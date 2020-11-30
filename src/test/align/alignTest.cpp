#include <iostream>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <faceBodyDetect/faceBodyDetect.hpp>
#include <align/align.hpp>

using namespace std;
using namespace cv;

int main() {

    Mat imgToAlign = imread("images/rotated_vaibhav.jpg", IMREAD_COLOR);
    Mat imgReference = imread("images/vaibhav.jpg", IMREAD_COLOR);

    assert (!imgToAlign.empty());
    assert (!imgReference.empty());

    FaceBodyDetection *faceBodyDetection = new HaarCascade();
    FaceBodyBoundingBoxes faceBody1 = faceBodyDetection->detect(imgToAlign);
    FaceBodyBoundingBoxes faceBody2 = faceBodyDetection->detect(imgReference);
    delete faceBodyDetection;

    alignImage(imgToAlign, imgReference, faceBody1.body, faceBody2.body);

    imshow("Aligned Image", imgToAlign);
    (void) waitKey(0);

    return 0;
}
