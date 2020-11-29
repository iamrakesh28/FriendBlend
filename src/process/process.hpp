#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <opencv2/core/mat.hpp>

using namespace cv;

enum ContrastStretchMethod {
    EACH_CHANNEL_INDEPENDENT,
    ON_Y_CHANNEL
};

void contrastStretch(
    Mat &img, 
    ContrastStretchMethod method = ON_Y_CHANNEL
);

void histogramEqualize(Mat &img);

#endif
