#include <iostream>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "process/process.hpp"

using namespace std;
using namespace cv;

int main() {

    string imgPath = "../images/vaderBright.jpeg";
    Mat inputImage = imread(imgPath, IMREAD_COLOR);
    Mat image;

    image = inputImage.clone();
    contrastStretch(image, ON_Y_CHANNEL);
    imshow("Contrast Stretched Image - Y Channel", image);
    (void) waitKey(0);

    image = inputImage.clone();
    contrastStretch(image, EACH_CHANNEL_INDEPENDENT);
    imshow("Contrast Stretched Image - Y Channel", image);
    (void) waitKey(0);

    return 0;
}
