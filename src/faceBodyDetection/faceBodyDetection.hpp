#ifndef FACE_BODY_DETECTION_HPP
#define FACE_BODY_DETECTION_HPP

#include <opencv2/core/mat.hpp>
#include "utility/utility.hpp"

class FaceBodyDetection {

    public:

    FaceBodyDetection() {}

    virtual ~FaceBodyDetection() {}

    virtual FaceBodyBoundingBoxes detect(const Mat &img) = 0;
};

#endif
