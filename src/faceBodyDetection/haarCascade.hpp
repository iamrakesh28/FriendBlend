#ifndef HAAR_CASCADE_HPP
#define HAAR_CASCADE_HPPs

#include <opencv2/core/mat.hpp>
#include <opencv2/objdetect.hpp>
#include <string>
#include "faceBodyDetection/faceBodyDetection.hpp"
#include "utility/utility.hpp"

using namespace std;
using namespace cv; 

class HaarCascade : public FaceBodyDetection {

	private:

	const string faceCasecadeLoc;
	CascadeClassifier faceCascade;

	public:
	
	HaarCascade();

	virtual ~HaarCascade();
	
	virtual FaceBodyBoundingBoxes detect(Mat &img);
};

#endif
