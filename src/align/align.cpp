#include <vector>
#include <algorithm>
#include <opencv2/core/mat.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/imgproc.hpp>
#include <align/align.hpp>

using namespace std;
using namespace cv;

void prunePoints(
    vector<KeyPoint> &keypoints,
    const BoundingBox &body
) {
    Point2f topLeft(body.topLeft.c, body.topLeft.r);
    Point2f bottomRight(body.bottomRight.c, body.bottomRight.r);

    vector<KeyPoint> keyOut;

    for(const KeyPoint &keypoint : keypoints) {
        Point2f point = keypoint.pt;
        if(
            topLeft.x <= point.x && point.x <= bottomRight.x
            &&
            topLeft.y <= point.y && point.y <= bottomRight.y
        )
            keyOut.push_back(keypoint);
    }

    keypoints = keyOut;
}

void pruneMatches(
    vector<DMatch> &matches,
    double pruneFraction
) {
    const int numGoodMatches = 
        static_cast<int>(matches.size() * pruneFraction);

    sort(matches.begin(), matches.end());
    matches.erase(matches.begin() + numGoodMatches, matches.end());
}

void keypointDetection(
    Ptr<Feature2D> &orb, Mat &image, const BoundingBox &body,
    vector<KeyPoint> &keypoints, Mat &descriptors
) {
    orb->detect(image, keypoints);
    prunePoints(keypoints, body);
    orb->compute(image, keypoints, descriptors);
}

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
    const BoundingBox &body1,
    const BoundingBox &body2
) {
    Mat imgToAlignGray, imgReferenceGray;
    cvtColor(imgToAlign, imgToAlignGray, COLOR_BGR2GRAY);
    cvtColor(imgReference, imgReferenceGray, COLOR_BGR2GRAY);

    Ptr<Feature2D> orb = ORB::create(MAX_FEATURES);

    vector<KeyPoint> keypoints1, keypoints2;
    Mat descriptors1, descriptors2;
    keypointDetection(orb, imgToAlignGray, body1, keypoints1, descriptors1);
    keypointDetection(orb, imgReferenceGray, body2, keypoints2, descriptors2);

    vector<DMatch> matches;
    keypointMatching(descriptors1, descriptors2, matches);

    vector<Point2f> points1, points2;
    for(size_t i = 0; i < matches.size(); i++ ) {
        points1.push_back(keypoints1[matches[i].queryIdx].pt);
        points2.push_back(keypoints2[matches[i].trainIdx].pt);
    }

    Mat homography = findHomography(points1, points2, RANSAC);
    warpPerspective(imgToAlign, imgToAlign, homography, imgReference.size());
}
