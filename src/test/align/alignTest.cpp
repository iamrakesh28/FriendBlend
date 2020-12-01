#include <iostream>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <faceBodyDetect/faceBodyDetect.hpp>
#include <align/align.hpp>

using namespace std;
using namespace cv;

int main() {

    Mat imgToAlign = imread("images/align/md_rotate.jpg", IMREAD_COLOR);
    Mat imgReference = imread("images/align/md.jpg", IMREAD_COLOR);

    assert (!imgToAlign.empty());
    assert (!imgReference.empty());

    Mat imageAlign = imgToAlign.clone();
    FaceBodyDetection *faceBodyDetection = new HaarCascade();
    FaceBodyBoundingBoxes faceBody1 = faceBodyDetection->detect(imageAlign);
    FaceBodyBoundingBoxes faceBody2 = faceBodyDetection->detect(imgReference);
    delete faceBodyDetection;

    alignImage(imageAlign, imgReference, faceBody1.body, faceBody2.body);

    imshow("Aligned Image", imageAlign);
    imshow("Original Image", imgToAlign);
    (void) waitKey(0);

    return 0;
}
