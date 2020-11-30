#include <opencv2/core/mat.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream> 
#include <algorithm>
#include "faceBodyDetection/haarCascade.hpp"

using namespace std;
using namespace cv; 
	
HaarCascade::HaarCascade() {
	// path of the face cascade
	string faceCascadePath = 
		"/usr/local/share/opencv4/"
		"haarcascades/haarcascade_frontalface_alt.xml";
		
	// load the face cascade
	if (!faceCascade.load(faceCascadePath)) {
		cout << "--(!)Error loading face cascade\n";
		exit(0);
	};
}

HaarCascade::~HaarCascade() {}

static bool comparator(Rect &recta, Rect &rectb) {
	return recta.height * recta.width > recta.height * rectb.width;
}
 
FaceBodyBoundingBoxes HaarCascade::detect(Mat &img) {

	Mat imgGray;
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	equalizeHist(imgGray, imgGray);
	
	// Detect faces
	std::vector <Rect> faces;
	faceCascade.detectMultiScale(imgGray, faces);
	sort(faces.begin(), faces.end(), comparator);
	
	if (faces.size() <= 0)
		return;
		
	Rect bigFace = faces[0];
	int faceWidth = bigFace.width;
	int faceHeight = bigFace.height;
	Point topLeft(bigFace.x - faceWidth, bigFace.y - faceHeight);
	Point bottomRight(bigFace.x + 2 * faceWidth, img.size().height);

	Position faceTopLeft (bigFace.y - faceHeight, bigFace.x - faceWidth);
	Position faceBottomRight;

	Position bodyTopLeft;
	Position bodyBottomRight;

	FaceBodyBoundingBoxes faceBodyBoundingBoxes (
		BoundingBox(faceTopLeft, faceBottomRight),
		BoundingBox(bodyTopLeft, bodyBottomRight)
	);

	return faceBodyBoundingBoxes;
}
