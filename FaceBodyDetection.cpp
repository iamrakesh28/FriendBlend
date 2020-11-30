#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream> 
#include <algorithm>

using namespace std; 
using namespace cv; 


class HaarCascade {
	const string faceCasecadeLoc;
	CascadeClassifier faceCascade;
public:
	HaarCascade() {
		// path of the face cascade
 		string faceCascadePath = "/usr/local/share/opencv4/"
			"haarcascades/haarcascade_frontalface_alt.xml";
		// load the face cascade
		if (!faceCascade.load(faceCascadePath)) {
			cout << "--(!)Error loading face cascade\n";
			exit(0);
		};
	}

	static bool comparator(Rect &recta, Rect &rectb) {
		return recta.height * recta.width > recta.height * rectb.width;
	}
	
	void detect(Mat &img) {
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
		Point bottRight(bigFace.x + 2 * faceWidth, img.size().height);
		rectangle(img, topLeft, bottRight, Scalar(0, 255, 0), 2, LINE_8);
		imshow( "Capture - Face detection", img);
	}  
	~HaarCascade() {}

  
};

int main( int argc, const char** argv ) 
{
  
    std::string image_path = "alexxis.jpg";
    Mat img = imread(image_path, IMREAD_COLOR);
    if(img.empty())
    {
        std::cout << "Could not read the image: " << image_path << std::endl;
        return 1;
    }
    HaarCascade face;
    face.detect( img );
    int k = waitKey(0);

    return 0;
     
} 

