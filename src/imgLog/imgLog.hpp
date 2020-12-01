#ifndef IMAGE_LOG_HPP
#define IMAGE_LOG_HPP

#include <string>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace std;
using namespace cv;

/** Singleton Logger Class */
class ImageLog {
    private:

    /** Directory where logged images would appear */
    const string logDir;

    /** Counter to mark current logged image */
    int counter;

    /** Should log image or not */
    bool imgLog;
    
    /** Should Add the image count to image name or not */
    bool addCounterToImageName;

    /** The logger */
    static ImageLog *logger;

    /** Private Constructor */
    ImageLog();

    public:

    /** Destructor */
    ~ImageLog();

    /** Should enable logging */
    inline void enableLogging(bool imgLog_) {imgLog = imgLog_;}

    /** Is logging enabled */
    inline bool enabled() {return imgLog;}

    /** Should add counter to image name */
    inline void shouldAddCounterToImageName(bool addCounterToImageName_) {
        addCounterToImageName = addCounterToImageName_;
    }

    /** Log provided image with provided name if logging is enabled */
    void logImage(
        const Mat &image, 
        const string imageName = "image"
    );

    /** Get the logger ! */
    static ImageLog& getLogger();
};

#endif
