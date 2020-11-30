#include <opencv2/core/mat.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream> 
#include <algorithm>
#include <cassert>
#include "faceBodyDetect/haarCascade.hpp"

using namespace std;
using namespace cv; 
	
HaarCascade::HaarCascade() {
	// path of the face cascade
	string faceCascadePath = 
		"/usr/local/share/opencv4/"
		"haarcascades/haarcascade_frontalface_alt.xml";
		
	// load the face cascade
	assert (faceCascade.load(faceCascadePath));
}

HaarCascade::~HaarCascade() {}

/** Comparator for sorting rectangles based on area */
static bool comparator(Rect &recta, Rect &rectb) {
	return recta.height * recta.width > recta.height * rectb.width;
}
 
FaceBodyBoundingBoxes HaarCascade::detect(const Mat &img) {

	Mat imgGray;
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	equalizeHist(imgGray, imgGray);
	
	// Detect faces
	std::vector <Rect> faces;
	faceCascade.detectMultiScale(imgGray, faces);
	sort(faces.begin(), faces.end(), comparator);
	
	assert (faces.size() > 0);
		
	Rect bigFace = faces[0];

	Position faceTopLeft (
		bigFace.y, 
		bigFace.x
	);

	Position faceBottomRight (
		bigFace.y + bigFace.height - 1,
		bigFace.x + bigFace.width - 1
	);

	Position bodyTopLeft (
		bigFace.y - bigFace.height,
		bigFace.x - bigFace.width
	);

	Position bodyBottomRight (
		img.size().height - 1,
		bigFace.x + 2 * bigFace.width
	);

	FaceBodyBoundingBoxes faceBodyBoundingBoxes (
		BoundingBox(faceTopLeft, faceBottomRight),
		BoundingBox(bodyTopLeft, bodyBottomRight)
	);

	return faceBodyBoundingBoxes;
}
