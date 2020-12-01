#include <opencv2/core/mat.hpp>
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

    
}

Mat blend(
    const Mat &inputImg1, const Mat &inputImg2,
    const FaceBodyBoundingBoxes &faceBody1,
    const FaceBodyBoundingBoxes &faceBody2
) {
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
