#include <iostream>
#include <vector>
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
        Mat image = inputImage.clone();

        clahe(image);
        imshow("CLAHE performed on Image", image);
        imshow("Original Image", inputImage);
        (void) waitKey(0);
    }

    return 0;
}
