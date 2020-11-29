#include <iostream>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "process/process.hpp"

using namespace std;
using namespace cv;

int main() {

    string imgPath = "../images/testImg.jpeg";
    Mat image = imread(imgPath, IMREAD_COLOR);

    contrastStretch(image);
    imshow("Contrast Stretched Image", image);
    (void) waitKey(0);

    return 0;
}
