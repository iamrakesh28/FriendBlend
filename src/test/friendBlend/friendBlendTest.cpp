#include <iostream>
#include <vector>
#include <cassert>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <friendBlend/friendBlend.hpp>

using namespace std;
using namespace cv;

int main() {

    vector<string> testDir = {"images/test1", "images/test2"};

    for(const string &dir : testDir) {
        Mat friend1 = imread(dir + "/friend1.jpg", IMREAD_COLOR);
        Mat friend2 = imread(dir + "/friend2.jpg", IMREAD_COLOR);

        assert (!friend1.empty());
        assert (!friend2.empty());

        Mat outImg = friendBlend(friend1, friend2);
        imshow("Blended Image", outImg);
        (void) waitKey(0);
    }

    return 0;
}
