#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>
#include <utility/utility.hpp>
#include <colorCorrect/colorCorrect.hpp>
#include <faceBodyDetect/faceBodyDetect.hpp>
#include <align/align.hpp>
#include <blend/blend.hpp>
#include <imgLog/imgLog.hpp>
#include <friendBlend/friendBlend.hpp>

using namespace cv;

/** Get a Color Correction Algorithm */
ColorCorrection* getColorCorrection() {
    return new HistogramEqualizeMethod();
}

/** Get a Face and Body Detection Algorithm */
FaceBodyDetection* getFaceBodyDetection() {
    return new HaarCascade();
}

/** Log the detected face and body for the images */
void performLogging(
    const Mat &inputImg1, const Mat &inputImg2,
    const FaceBodyBoundingBoxes &faceBody1,
    const FaceBodyBoundingBoxes &faceBody2
) {
    // Log Image 1
    Mat img1 = inputImg1.clone();
    rectangle(
        img1, faceBody1.face.topLeft, faceBody1.face.bottomRight, 
        Scalar(0, 255, 0), 2, LINE_8
    );
    rectangle(
        img1, faceBody1.body.topLeft, faceBody1.body.bottomRight, 
        Scalar(255, 0, 0), 2, LINE_8
    );
    ImageLog::getLogger().logImage(img1, "faceDetImg1");
    
    // Log Image 2
    Mat img2 = inputImg2.clone();
    rectangle(
        img2, faceBody2.face.topLeft, faceBody2.face.bottomRight, 
        Scalar(0, 255, 0), 2, LINE_8
    );
    rectangle(
        img2, faceBody2.body.topLeft, faceBody2.body.bottomRight, 
        Scalar(255, 0, 0), 2, LINE_8
    );
    ImageLog::getLogger().logImage(img2, "faceDetImg2");
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

    if(ImageLog::getLogger().enabled())
        performLogging(img1, img2, faceBody1, faceBody2);

    alignImage(img2, img1, faceBody2.body, faceBody1.body);

    return blend(img1, img2, faceBody1, faceBody2);
}
