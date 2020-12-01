#include <iostream>
#include <cassert>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <faceBodyDetect/faceBodyDetect.hpp>
#include <utility/utility.hpp>
#include <blend/blend.hpp>

using namespace std;
using namespace cv;

int main() {

    Mat friend1 = imread("rahul_friend", IMREAD_COLOR);
    Mat friend2 = imread("devansh_friend", IMREAD_COLOR);

    assert (!friend1.empty());
    assert (!friend2.empty());

    FaceBodyDetection *faceBodyDetection = new HaarCascade();
    FaceBodyBoundingBoxes faceBody1 = faceBodyDetection->detect(friend1);
    FaceBodyBoundingBoxes faceBody2 = faceBodyDetection->detect(friend2);
    delete faceBodyDetection;

    Mat outImg = blend(friend1, friend2, faceBody1, faceBody2);
    imshow("Blended Image", outImg);
    (void) waitKey(0);

    return 0;
}
