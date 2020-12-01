#include <opencv2/core/mat.hpp>
#include <utility/utility.hpp>
#include <blend/blend.hpp>

using namespace cv;

int computeArea(const BoundingBox &boundingBox) {
    return (boundingBox.bottomRight.r - boundingBox.topLeft.r)
    * (boundingBox.bottomRight.c - boundingBox.topLeft.c);
}

Mat grabCut(
    const Mat &inputImg1, const Mat &inputImg2,
    const FaceBodyBoundingBoxes &faceBody1,
    const FaceBodyBoundingBoxes &faceBody2
) {
    Mat outImg, personImg;
    const FaceBodyBoundingBoxes person;

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

    
}

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
            Vec3b &leftColor = inputImg1.at <Vec3b> (row, col);
            Vec3b &rightColor = inputImg1.at <Vec3b> (row, col);
            
            Vec3b newColor = blendColor(leftColor, rightColor, stepSize, stepCount);
            outImg.at <Vec3b> (row, col) = newColor;
        }
    }
    
    return outImg;
}

Mat blend(
    const Mat &inputImg1, const Mat &inputImg2,
    const FaceBodyBoundingBoxes &faceBody1,
    const FaceBodyBoundingBoxes &faceBody2
) {
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

    if(distance >= DISTANCE_THRESHOLD)
        return grabCut(img1, img2, faceBody1, faceBody2);
}
