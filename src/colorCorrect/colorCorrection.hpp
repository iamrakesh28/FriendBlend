#ifndef COLOR_CORRECTION_HPP
#define COLOR_CORRECTION_HPP

#include <opencv2/core/mat.hpp>

using namespace cv;

/** Base Class for Color Correction */
class ColorCorrection {

    public:

    /** Constructor */
    ColorCorrection() {}

    /** Virtual Destructor */
    virtual ~ColorCorrection() {}

    /**
     * Performs Color Correction between two images
     * 
     * @param img The first image in BGR format, this image is itself modified
     * @param img The second image in BGR format, this image is itself modified
     */
    virtual void colorCorrect(Mat &img1, Mat &img2) = 0;
};

#endif
