#ifndef CLAHE_METHOD_HPP
#define CLAHE_METHOD_HPP

#include <opencv2/core/mat.hpp>
#include <colorCorrect/colorCorrection.hpp>

using namespace cv;

/** CLAHE based method for Color Correction between two images */
class ClaheMethod : public ColorCorrection {

    public:

    /** Constructor */
    ClaheMethod();

    /** Destructor */
    virtual ~ClaheMethod();

    /**
     * Performs Color Correction between two images
     * 
     * @param img The first image in BGR format, this image is itself modified
     * @param img The second image in BGR format, this image is itself modified
     */
    virtual void colorCorrect(Mat &img1, Mat &img2);
};

#endif
