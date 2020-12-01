#ifndef IMAGE_LOG_HPP
#define IMAGE_LOG_HPP

#include <string>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace std;
using namespace cv;

class ImageLog {
    private:

    const string logDir;
    int counter;
    bool imgLog, addCounterToImageName;

    static ImageLog *logger = nullptr;

    ImageLog();

    public:

    ~ImageLog();

    inline void shouldLog(bool imgLog_) {imgLog = imgLog_;}

    inline bool isLogging() {return imgLog;}

    inline void shouldAddCounterToImageName(bool addCounterToImageName_) {
        addCounterToImageName = addCounterToImageName_;
    }

    void logImage(
        const Mat &image, 
        const string &imageName = "image"
    );

    static ImageLog& getLogger();
};

#endif
