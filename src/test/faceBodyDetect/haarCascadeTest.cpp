#include <iostream>
#include <vector>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <faceBodyDetect/faceBodyDetect.hpp>
#include <utility/utility.hpp>
#include <process/process.hpp>

using namespace std;
using namespace cv;

void testOnImage(const string &imgPath) {
    Mat image = imread(imgPath, IMREAD_COLOR);

    FaceBodyDetection *faceBodyDetection = new HaarCascade();
    FaceBodyBoundingBoxes faceBody = faceBodyDetection->detect(image);
    delete faceBodyDetection;

    // Draw Bounding Box about the face
    rectangle(
        image, faceBody.face.topLeft, faceBody.face.bottomRight, 
        Scalar(0, 255, 0), 2, LINE_8
    );

    // Draw Bounding Box about the body
    rectangle(
        image, faceBody.body.topLeft, faceBody.body.bottomRight, 
        Scalar(255, 0, 0), 2, LINE_8
    );

    imshow("Face and Body Detection Image", image);
    (void) waitKey(0);
}

int main() {

    vector<string> imagePaths = {
        "images/test1/friend1.jpg",
        "images/test1/friend2.jpg",
	    "images/devansh1.jpg",
        "images/devansh2.jpg",
        "images/rahul1.jpg",
        "images/rahul2.jpg",
        "images/md.jpg",
        "images/vaibhav.jpg",
        "images/ahmed.jpg",
        "images/alexxis.jpg"
    };
    
    for(const string &imgPath : imagePaths)
        testOnImage(imgPath);

    return 0;
}
