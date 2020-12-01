#include <string>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <imgLog/imgLog.hpp>

using namespace std;
using namespace cv;

ImageLog* ImageLog::logger = nullptr;

ImageLog::ImageLog():
    logDir("logs/"), counter(0),
    imgLog(false), addCounterToImageName(true) {}

void ImageLog::logImage(
    const Mat &image, 
    const string imageName
) {
    string addCounter = "";
    if(addCounterToImageName)
        addCounter += "_" + to_string(counter);

    if(imgLog)
        imwrite(logDir + imageName + addCounter + ".jpg", image);

    counter ++;
}

ImageLog& ImageLog::getLogger() {
    if(logger == nullptr)
        logger = new ImageLog();

    return *logger;
}
