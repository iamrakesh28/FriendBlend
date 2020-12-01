#include <opencv2/core/mat.hpp>
#include <utility/utility.hpp>
#include <colorCorrect/colorCorrect.hpp>
#include <faceBodyDetect/faceBodyDetect.hpp>
#include <align/align.hpp>
#include <blend/blend.hpp>
#include <friendBlend/friendBlend.hpp>

using namespace cv;

ColorCorrection* getColorCorrection() {
    return new ClaheMethod();
}

FaceBodyDetection* getFaceBodyDetection() {
    return new HaarCascade();
}

Mat friendBlend(const Mat &inputImg1, const Mat &inputImg2) {
    Mat img1 = inputImg1.clone();
    Mat img2 = inputImg2.clone();

    ColorCorrection *colorCorrection = getColorCorrection();
    colorCorrection->colorCorrect(img1, img2);
    delete colorCorrection;

    FaceBodyDetection *faceBodyDetection = getFaceBodyDetection();
    FaceBodyBoundingBoxes faceBody1 = faceBodyDetection->detect(img1);
    FaceBodyBoundingBoxes faceBody2 = faceBodyDetection->detect(img2);
    delete faceBodyDetection;

    alignImage(img2, img1, faceBody2.body, faceBody1.body);

    return blend(img1, img2, faceBody1, faceBody2);
}
