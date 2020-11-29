#ifndef CLAHE_METHOD_HPP
#define CLAHE_METHOD_HPP

#include <opencv2/core/mat.hpp>
#include <colorCorrect/colorCorrection.hpp>

using namespace cv;

class ClaheMethod : public ColorCorrection {

    public:

    ClaheMethod();

    virtual ~ClaheMethod();

    virtual void colorCorrect(Mat &img1, Mat &img2);
};

#endif
