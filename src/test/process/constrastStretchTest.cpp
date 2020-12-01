#include <iostream>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "process/process.hpp"

using namespace std;
using namespace cv;

int main() {

    vector<string> imgPaths = {
        "images/process/vaderBright.jpeg",
        "images/process/carBright.jpg"
    };

    for(const string &imgPath : imgPaths) {
        Mat inputImage = imread(imgPath, IMREAD_COLOR);
        Mat imageContrastY = inputImage.clone();
        Mat imageEachIndep = inputImage.clone();

        contrastStretch(imageContrastY, ON_Y_CHANNEL);
        contrastStretch(imageEachIndep, EACH_CHANNEL_INDEPENDENT);

        imshow("Original Image", inputImage);
        imshow("Contrast Stretched Image - Y Channel", imageContrastY);
        imshow("Contrast Stretched Image - Independent", imageEachIndep);
        (void) waitKey(0);
    }    

    return 0;
}
