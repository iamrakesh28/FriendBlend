#include <cassert>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/imgproc.hpp>
#include <utility/utility.hpp>
#include <blend/blend.hpp>

using namespace cv;

/**
 * Computes the area of the bounding box
 *
 * @param boundingBox a rectangular box
 * @return area of the bounding box 
 */

int computeArea(const BoundingBox &boundingBox) {
    return (boundingBox.bottomRight.r - boundingBox.topLeft.r)
    * (boundingBox.bottomRight.c - boundingBox.topLeft.c);
}

/**
 * Uses grabCut to blend the two input images
 *
 * @param inputImg1 image having a person  in the left side
 * @param inputImg2 image having a person in the right side
 * @param faceBody1 bounding boxes for the face and body in inputImg1
 * @param faceBody2 bounding boxes for the face and body in inputImg2
 * @return blended image 
 */

Mat grabCut(
    const Mat &inputImg1, const Mat &inputImg2,
    const FaceBodyBoundingBoxes &faceBody1,
    const FaceBodyBoundingBoxes &faceBody2
) {
    Mat outImg, personImg;
    FaceBodyBoundingBoxes person;

    if(computeArea(faceBody1.face) <= computeArea(faceBody2.face)) {
        outImg = inputImg1;
        personImg = inputImg2;
        person = faceBody2;
    }
    else {
        outImg = inputImg2;
        personImg = inputImg1;
        person = faceBody1;
    }

    // Mask initialized completely with obvious background
    Mat mask (personImg.rows, personImg.cols, CV_8UC1, GC_BGD);
    rectangle( // Body is probable foreground
        mask, person.body.topLeft, person.body.bottomRight, 
        GC_PR_FGD, FILLED
    );
    rectangle( // Face is obvious foreground
        mask, person.face.topLeft, person.face.bottomRight, 
        GC_FGD, FILLED
    );

    // Perform GrabCut
    Mat bgModel, fgModel;
    cv::grabCut(
        personImg, mask, Rect(), 
        bgModel, fgModel,
        GC_INIT_WITH_MASK
    );

    // Place foreground on background
    for(int r = 0; r < outImg.rows;r++) {
        for(int c = 0;c < outImg.cols;c++) {
            uchar maskVal = mask.at<uchar>(r, c);

            if(maskVal == GC_FGD || maskVal == GC_PR_FGD)
                outImg.at<Vec3b>(r, c) = personImg.at<Vec3b>(r, c);
        }
    }

    return outImg;
}

/**
 * Blends a position in the image using Alpha Blending
 * Used in the intermediate step of alphaBlend function
 *
 * @param leftColor color at a position of the left image
 * @param rightColor color at a position of the right image
 * @param stepSize one of the parameter used to find alpha
 * @param stepCount one of the parameter used to find alpha 
 * @return blended color at the given position
 */

Vec3b blendColor(
    const Vec3b &leftColor,
    const Vec3b &rightColor,
    float stepSize,
    int stepCount
) {
  
	Vec3b newColor;
	float alpha = stepCount * stepSize;
	for (int channel = 0; channel < 3; channel++) {
		float intensity = (1 - alpha) * leftColor.val[channel]
			+ alpha * rightColor.val[channel];
		newColor.val[channel] = uchar(intensity);
	}
	
	return newColor;
}

/**
 * Uses Alpha Blending to blend the two input images
 *
 * @param inputImg1 image having a person in the left side
 * @param inputImg2 image having a person in the right side
 * @param faceBody1 bounding boxes for the face and body in inputImg1
 * @param faceBody2 bounding boxes for the face and body in inputImg2 
 * @return blended image
 */

Mat alphaBlend(
    const Mat &inputImg1, const Mat &inputImg2, 
    const FaceBodyBoundingBoxes &faceBody1,
    const FaceBodyBoundingBoxes &faceBody2
) {

    Mat outImg = inputImg1.clone();
    
    int colStart = faceBody1.body.bottomRight.c;
    int colEnd = faceBody2.body.topLeft.c;

    /** copy the inputImg2 content right of colEnd */
    for (int col = colEnd + 1; col < inputImg2.cols; col++) {
        for (int row = 0; row < inputImg2.rows; row++) {
            Vec3b color = inputImg2.at <Vec3b> (row, col);
            outImg.at <Vec3b> (row, col) = color;
        }
    }

	float stepSize = 1 / (float)(colEnd - colStart);
	
    /** performs alpha blending  */
    for (int col = colStart; col <= colEnd; col++) {
    	int stepCount = col - colStart;
        for (int row = 0; row < inputImg2.rows; row++) {
            Vec3b leftColor = inputImg1.at <Vec3b> (row, col);
            Vec3b rightColor = inputImg1.at <Vec3b> (row, col);
            
            Vec3b newColor = blendColor(leftColor, rightColor, stepSize, stepCount);
            outImg.at <Vec3b> (row, col) = newColor;
        }
    }
    
    return outImg;
}

/**
 * Blends the two input images using GrabCut or Alpha Blending algorithms
 *
 * @param inputImg1 first image having a person
 * @param inputImg2 second image having a person
 * @param faceBody1 bounding boxes for the face and body in inputImg1
 * @param faceBody2 bounding boxes for the face and body in inputImg2 
 * @return blended image
 */

Mat blend(
    const Mat &inputImg1, const Mat &inputImg2,
    const FaceBodyBoundingBoxes &faceBody1,
    const FaceBodyBoundingBoxes &faceBody2
) {
    assert (
        inputImg1.rows == inputImg2.rows
        &&
        inputImg1.cols == inputImg2.cols
    );

    Mat img1, img2;

    if(faceBody1.body.topLeft.c <= faceBody2.body.topLeft.c) {
        img1 = inputImg1.clone();
        img2 = inputImg2.clone();
    }
    else {
        img1 = inputImg2.clone();
        img2 = inputImg1.clone();
    }

    int distance = faceBody2.body.topLeft.c - faceBody1.body.bottomRight.c;

    if(distance < DISTANCE_THRESHOLD)
        return grabCut(img1, img2, faceBody1, faceBody2);
    return alphaBlend(img1, img2, faceBody1, faceBody2);
}
