#include <iostream>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "colorCorrect/colorCorrect.hpp"

using namespace std;
using namespace cv;

int main() {

    Mat img1 = imread("images/ghostBright.jpg", IMREAD_COLOR);
    Mat img2 = imread("images/ghostDark.jpg", IMREAD_COLOR);

    assert(!img1.empty());
    assert(!img2.empty());

    ColorCorrection *colorCorrect = new HistogramEqualizeMethod();

    colorCorrect->colorCorrect(img1, img2);
    delete colorCorrect;

    imshow("Image 1", img1);
    imshow("Image 2", img2);

    (void) waitKey(0);

    return 0;
}
