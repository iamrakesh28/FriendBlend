#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <opencv2/core/mat.hpp>

using namespace cv;

/** Contrast Stretching Method */
enum ContrastStretchMethod {
    EACH_CHANNEL_INDEPENDENT, // Perform Independently on each channel
    ON_Y_CHANNEL // Perform on Y Channel after converting to YCrCb and then back
};

/**
 * Perform Constrast Stretching on the image using the provided method
 * 
 * @param img The image in BGR format, this image is itself modified
 * @param method The Contrast Stretching method
 */
void contrastStretch(
    Mat &img, 
    ContrastStretchMethod method = ON_Y_CHANNEL
);

/**
 * Perform Histogram Equalization on the image
 * 
 * @param img The image in BGR format, this image is itself modified
 */
void histogramEqualize(Mat &img);

/**
 * Perform Contrast Limited Adaptive Histogram Equalization on the image
 * 
 * @param img The image in BGR format, this image is itself modified
 */
void clahe(Mat &img);

#endif
