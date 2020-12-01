#include <vector>
#include <algorithm>
#include <opencv2/core/mat.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/imgproc.hpp>
#include <imgLog/imgLog.hpp>
#include <align/align.hpp>

using namespace std;
using namespace cv;

/**
 * Prunes keypoints which are present in the bounding box
 * 
 * @param keypoints Vector of keypoints, this itself is modified
 * @param body Body bounding box
 */
void prunePoints(
    vector<KeyPoint> &keypoints,
    const BoundingBox &body
) {
    Point2f topLeft(body.topLeft.c, body.topLeft.r);
    Point2f bottomRight(body.bottomRight.c, body.bottomRight.r);

    vector<KeyPoint> keyOut;

    for(const KeyPoint &keypoint : keypoints) {
        Point2f point = keypoint.pt;
        // Keypoint must lie outside of bounding box
        if(
            topLeft.x > point.x || point.x > bottomRight.x
            ||
            topLeft.y > point.y || point.y > bottomRight.y
        )
            keyOut.push_back(keypoint);
    }

    keypoints = keyOut;
}

/**
 * Prune the matches by removing a fraction of the least matched matches
 * 
 * @param matches Vector of matches, this itself is modified
 * @param pruneFraction Fraction of least matched matches to remove
 */
void pruneMatches(
    vector<DMatch> &matches,
    double pruneFraction
) {
    const int numGoodMatches = 
        static_cast<int>(matches.size() * pruneFraction);

    sort(matches.begin(), matches.end());
    matches.erase(matches.begin() + numGoodMatches, matches.end());
}

/**
 * Perform keypoint detection using ORB algorithm and prune results
 * based on the provided bounding box for the person body
 * 
 * @param orb ORB algorithm interface
 * @param image The image, it is a Grayscale image
 * @param body The body bounding box
 * @param keypoints Keypoints would be outputted in this variable
 * @param descriptors Descriptors would be outputted in this variable
 */
void keypointDetection(
    Ptr<Feature2D> &orb, Mat &image, const BoundingBox &body,
    vector<KeyPoint> &keypoints, Mat &descriptors
) {
    orb->detect(image, keypoints);
    prunePoints(keypoints, body);
    orb->compute(image, keypoints, descriptors);
}

/**
 * Performs Keypoint Matching using Brute Force Matching
 * and prunes least matched matches 
 * 
 * @param descriptors1 Descriptors of the first image
 * @param descriptors2 Descriptors of the second image
 * @param matches Matches would be outputted in this variable
 */
void keypointMatching(
    Mat &descriptors1,
    Mat &descriptors2,
    vector<DMatch> &matches
) {
    Ptr<DescriptorMatcher> matcher = 
        DescriptorMatcher::create("BruteForce-Hamming");

    matcher->match(descriptors1, descriptors2, matches, Mat());
    pruneMatches(matches, GOOD_MATCH_PERCENT);
}

void alignImage(
    Mat &imgToAlign, 
    const Mat &imgReference, 
    const BoundingBox &bodyAlign,
    const BoundingBox &bodyReference
) {
    Mat imgToAlignGray, imgReferenceGray;
    cvtColor(imgToAlign, imgToAlignGray, COLOR_BGR2GRAY);
    cvtColor(imgReference, imgReferenceGray, COLOR_BGR2GRAY);

    Ptr<Feature2D> orb = ORB::create(MAX_FEATURES);

    vector<KeyPoint> keypoints1, keypoints2;
    Mat descriptors1, descriptors2;
    keypointDetection(orb, imgToAlignGray, bodyAlign, keypoints1, descriptors1);
    keypointDetection(orb, imgReferenceGray, bodyReference, keypoints2, descriptors2);

    if(ImageLog::getLogger().enabled()) {
        Mat keypointImageAlign, keypointImageReference;
        Scalar color (0, 0, 255);

        drawKeypoints(imgToAlign, keypoints1, keypointImageAlign, color);
        ImageLog::getLogger().logImage(keypointImageAlign, "imageToAlignKey");

        drawKeypoints(imgReference, keypoints2, keypointImageReference, color);
        ImageLog::getLogger().logImage(keypointImageReference, "imageReferenceKey");
    }

    vector<DMatch> matches;
    keypointMatching(descriptors1, descriptors2, matches);

    if(ImageLog::getLogger().enabled()) {
        Mat matchImage;
        drawMatches(
            imgToAlign, keypoints1, imgReference, keypoints2, 
            matches, matchImage
        );
        ImageLog::getLogger().logImage(matchImage, "matchImage");
    }

    vector<Point2f> points1, points2;
    for(size_t i = 0; i < matches.size(); i++ ) {
        points1.push_back(keypoints1[matches[i].queryIdx].pt);
        points2.push_back(keypoints2[matches[i].trainIdx].pt);
    }

    Mat homography = findHomography(points1, points2, RANSAC);
    warpPerspective(imgToAlign, imgToAlign, homography, imgReference.size());

    ImageLog::getLogger().logImage(imgToAlign, "alignedImage");
}
