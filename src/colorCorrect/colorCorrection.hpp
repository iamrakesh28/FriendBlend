#ifndef COLOR_CORRECTION_HPP
#define COLOR_CORRECTION_HPP

#include <opencv2/core/mat.hpp>

using namespace cv;

class ColorCorrection {

    public:

    ColorCorrection() {}

    virtual ~ColorCorrection() {}

    virtual void colorCorrect(Mat &img1, Mat &img2) = 0;
};

#endif
