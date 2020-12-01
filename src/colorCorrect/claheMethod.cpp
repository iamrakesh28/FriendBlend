#include <opencv2/core/mat.hpp>
#include <colorCorrect/claheMethod.hpp>
#include <process/process.hpp>
#include <imgLog/imgLog.hpp>

using namespace cv;

ClaheMethod::ClaheMethod() {}

ClaheMethod::~ClaheMethod() {}

void ClaheMethod::colorCorrect(Mat &img1, Mat &img2) {
    clahe(img1);
    clahe(img2);

    ImageLog::getLogger().logImage(img1, "claheImg1");
    ImageLog::getLogger().logImage(img2, "claheImg2");
}
