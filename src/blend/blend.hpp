#ifndef FRIEND_BLEND_HPP
#define FRIEND_BLEND_HPP

#include <opencv2/core/mat.hpp>
#include <utility/utility.hpp>

using namespace cv;

/** 
 * If distance between bounding boxes is equal or more than this
 * value, then we apply Alpha Blending, else we apply GrabCut
 */
const int DISTANCE_THRESHOLD = 200;

Mat blend(
    const Mat &inputImg1, const Mat &inputImg2,
    FaceBodyBoundingBoxes faceBody1,
    FaceBodyBoundingBoxes faceBody2
);

#endif
