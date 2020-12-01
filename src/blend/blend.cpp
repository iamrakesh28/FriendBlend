#include <cassert>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/imgproc.hpp>
#include <utility/utility.hpp>
#include <blend/blend.hpp>

using namespace cv;

int computeArea(const BoundingBox &boundingBox) {
    return (boundingBox.bottomRight.r - boundingBox.topLeft.r)
    * (boundingBox.bottomRight.c - boundingBox.topLeft.c);
}

Mat grabCut(
    const Mat &inputImg1, const Mat &inputImg2,
    const FaceBodyBoundingBoxes &faceBody1,
    const FaceBodyBoundingBoxes &faceBody2
) {
    Mat outImg, personImg;
    const FaceBodyBoundingBoxes person;

    if(computeArea(faceBody1.face) <= computeArea(faceBody2.face)) {
        outImg = inputImg1;
        personImg = inputImg2;
        person = faceBody2;
    }
    else {
        outImg = inputImg2;
        personImg = inputImg1;
        person = faceBody1;
    }

    // Mask initialized completely with obvious background
    Mat mask (personImg.rows, personImg.cols, CV_8UC1, GC_BGD);
    rectangle( // Body is probable foreground
        mask, person.body.topLeft, person.body.topRight, 
        GC_PR_FGD, FILLED
    );
    rectangle( // Face is obvious foreground
        mask, person.face.topLeft, person.fac.topRight, 
        GC_FGD, FILLED
    );

    // Perform GrabCut
    Mat bgModel, fgModel;
    cv::grabCut(
        personImg, mask, Rect(), 
        bgModel, fgModel,
        GC_INIT_WITH_MASK
    );

    // Place foreground on background
    for(int r = 0; r < outImg.rows;r++) {
        for(int c = 0;c < outImg.cols;c++) {
            uchar maskVal = mask.at<uchar>(r, c);

            if(maskVal == GC_FGD || maskVal == GC_PR_FGD)
                outImg.at<Vec3b>(r, c) = personImg.at<Vec3b>(r, c);
        }
    }

    return outImg;
}

Mat blend(
    const Mat &inputImg1, const Mat &inputImg2,
    const FaceBodyBoundingBoxes &faceBody1,
    const FaceBodyBoundingBoxes &faceBody2
) {
    assert (
        inputImg1.rows == inputImg2.rows
        &&
        inputImg1.cols == inputImg2.cols;
    );

    Mat img1, img2;

    if(faceBody1.body.topLeft.c <= faceBody2.body.topLeft.c) {
        img1 = inputImg1.clone();
        img2 = inputImg2.clone();
    }
    else {
        img1 = inputImg2.clone();
        img2 = inputImg1.clone();
    }

    int distance = faceBody2.body.topLeft.c - faceBody1.body.bottomRight.c;

    if(distance >= DISTANCE_THRESHOLD)
        return grabCut(img1, img2, faceBody1, faceBody2);
}
