#ifndef ALIGN_HPP
#define ALIGN_HPP

#include <opencv2/core/mat.hpp>
#include <utility/utility.hpp>

using namespace cv;

/** Maximum Number of Features */
const int MAX_FEATURES = 500;

/** Fraction of matches to remove */
const double GOOD_MATCH_PERCENT = 0.15f;

/**
 * Align the provided image with the referenced image. Each image
 * contains a person (different people most probably), bounding
 * boxes of the person in first image and bounding of the person
 * in the second image are also provided so that we may not consider
 * that region while aligning the provided image with the reference image.
 * 
 * @param imgToAlign Image which is to be aligned, it is in BGR format, this
 * image is itself modified
 * @param imgReference Reference image, it is in BGR format
 * @param bodyAlign Bounding Box of the person in the image which is to be aligned
 * @param bodyReference Bounding Box of the person in the reference image
 */
void alignImage(
    Mat &imgToAlign, 
    const Mat &imgReference, 
    const BoundingBox &bodyAlign,
    const BoundingBox &bodyReference
);

#endif
