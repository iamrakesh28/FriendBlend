#ifndef ALIGN_HPP
#define ALIGN_HPP

#include <opencv2/core/mat.hpp>
#include <utility/utility.hpp>

using namespace cv;

const int MAX_FEATURES = 500;
const double GOOD_MATCH_PERCENT = 0.15f;

void alignImage(
    Mat &imgToAlign, 
    const Mat &imgReference, 
    const BoundingBox &body1,
    const BoundingBox &body2
);

#endif
