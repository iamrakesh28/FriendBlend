#ifndef HAAR_CASCADE_HPP
#define HAAR_CASCADE_HPPs

#include <opencv2/core/mat.hpp>
#include <opencv2/objdetect.hpp>
#include <string>
#include "faceBodyDetection/faceBodyDetection.hpp"
#include "utility/utility.hpp"

using namespace std;
using namespace cv; 

/** Haar Cascade based Face Detection Algorithm */
class HaarCascade : public FaceBodyDetection {

	private:

	/** Location of Face Cascade in the Filesystem */
	const string faceCasecadeLoc;

	/** Face Cascade Classifier */
	CascadeClassifier faceCascade;

	public:
	
	/** Constructor */
	HaarCascade();

	/** Destructor */
	virtual ~HaarCascade();
	
	/**
     * Detect a Face and Body in the provided image
     * 
     * @param img The image in BGR format
     * @return Bounding Boxes for the Face and Body
     */
	virtual FaceBodyBoundingBoxes detect(Mat &img);
};

#endif
