#include <opencv2/core/mat.hpp>
#include "colorCorrect/claheMethod.hpp"
#include "process/process.hpp"

using namespace cv;

ClaheMethod::ClaheMethod() {}

ClaheMethod::~ClaheMethod() {}

void ClaheMethods::colorCorrect(Mat &img1, Mat &img2) {
    clahe(img1);
    clahe(img2);
}
