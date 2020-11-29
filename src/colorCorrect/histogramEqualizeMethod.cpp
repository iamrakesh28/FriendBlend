#include <opencv2/core/mat.hpp>
#include "colorCorrect/histogramEqualizeMethod.hpp"
#include "process/process.hpp"

using namespace cv;

HistogramEqualizeMethod::HistogramEqualizeMethod() {}

HistogramEqualizeMethod::~HistogramEqualizeMethod() {}

void HistogramEqualizeMethod::colorCorrect(Mat &img1, Mat &img2) {
    histogramEqualize(img1);
    histogramEqualize(img2);
}
