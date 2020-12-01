#include <iostream>
#include <cassert>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <imgLog/imgLog.hpp>
#include <friendBlend/friendBlend.hpp>

using namespace std;
using namespace cv;

int main(int argc, char *argv[]) {

    assert (argc == 3 || argc == 4);

    Mat friend1 = imread(string(argv[1]), IMREAD_COLOR);
    Mat friend2 = imread(string(argv[2]), IMREAD_COLOR);

    if(argc == 4 && (string(argv[3]) == "log"))   
        ImageLog::getLogger().enableLogging(true);

    assert (!friend1.empty());
    assert (!friend2.empty());

    Mat outImg = friendBlend(friend1, friend2);
    imshow("Blended Image", outImg);
    (void) waitKey(0);

    return 0;
}
