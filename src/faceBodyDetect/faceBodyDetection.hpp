#ifndef FACE_BODY_DETECTION_HPP
#define FACE_BODY_DETECTION_HPP

#include <opencv2/core/mat.hpp>
#include "utility/utility.hpp"

using namespace cv;

/** Face and Body Detection */
class FaceBodyDetection {

    public:

    /** Constructor */
    FaceBodyDetection() {}

    /** Virtual Destructor */
    virtual ~FaceBodyDetection() {}

    /**
     * Detect a Face and Body in the provided image
     * 
     * @param img The image in BGR format
     * @return Bounding Boxes for the Face and Body
     */
    virtual FaceBodyBoundingBoxes detect(const Mat &img) = 0;
};

#endif
