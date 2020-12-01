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

    vector<string> testDir = {
        "images/test1",
        "images/test5",
        "images/test6"
    };

    for(const string &dir : testDir) {
        Mat friend1 = imread(dir + "/friend1.jpg", IMREAD_COLOR);
        Mat friend2 = imread(dir + "/friend2.jpg", IMREAD_COLOR);

        assert (!friend1.empty());
        assert (!friend2.empty());

        FaceBodyDetection *faceBodyDetection = new HaarCascade();
        FaceBodyBoundingBoxes faceBody1 = faceBodyDetection->detect(friend1);
        FaceBodyBoundingBoxes faceBody2 = faceBodyDetection->detect(friend2);
        delete faceBodyDetection;

        Mat outImg = blend(friend1, friend2, faceBody1, faceBody2);
        imshow("Blended Image", outImg);
        (void) waitKey(0);
    }

    return 0;
}
