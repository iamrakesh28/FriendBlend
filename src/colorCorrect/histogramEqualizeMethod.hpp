#ifndef HISTOGRAM_EQUALIZE_HPP
#define HISTOGRAM_EQUALIZE_HPP

#include <opencv2/core/mat.hpp>
#include <colorCorrect/colorCorrection.hpp>

using namespace cv;

class HistogramEqualizeMethod : public ColorCorrection {

    public:

    HistogramEqualizeMethod();

    virtual ~HistogramEqualizeMethod();

    virtual void colorCorrect(Mat &img1, Mat &img2);
};

#endif
