#ifndef HISTOGRAM_EQUALIZE_METHOD_HPP
#define HISTOGRAM_EQUALIZE_METHOD_HPP

#include <opencv2/core/mat.hpp>
#include <colorCorrect/colorCorrection.hpp>

using namespace cv;

/** 
 * Histogram Equalization based method for Color Correction
 * between two images 
 */
class HistogramEqualizeMethod : public ColorCorrection {

    public:

    /** Constructor */
    HistogramEqualizeMethod();

    /** Destructor */
    virtual ~HistogramEqualizeMethod();

    /**
     * Performs Color Correction between two images
     * 
     * @param img The first image in BGR format, this image is itself modified
     * @param img The second image in BGR format, this image is itself modified
     */
    virtual void colorCorrect(Mat &img1, Mat &img2);
};

#endif
