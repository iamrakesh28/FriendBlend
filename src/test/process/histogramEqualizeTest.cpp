#include <iostream>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "process/process.hpp"

using namespace std;
using namespace cv;

int main() {

    string imgPath = "../images/vaderBright.jpeg";
    Mat image = imread(imgPath, IMREAD_COLOR);

    histogramEqualize(image);
    imshow("Histogram Equalized Image", image);
    (void) waitKey(0);

    return 0;
}
