#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <opencv2/core/types.hpp>

struct Position {
    /** row and column */
    int r, c;

    /** Construct Position using row and column values */
    Position(int r_, int c_);

    /** Copy Constructor */
    Position(const Position &pos);
  
    /** Default Constructor */
    Position();  

    /** Destructor */
    ~Position();

    /** Copy Assignment Operator */
    const Position& operator= (const Position &pos);

    /** Conversion to object of Opencv Point class */
    operator cv::Point();
};

struct BoundingBox {
    /** Top left and Bottom right positions */
    Position topLeft, bottomRight;

    /** Construct BoundingBox Top left and Bottom right positions */
    BoundingBox(
        const Position &topLeft_, 
        const Position &bottomRight_
    );

    /** Copy Constructor */
    BoundingBox(const BoundingBox &boundingBox);
  
    /** Default Constructor */
    BoundingBox();
  
    /** Destructor */
    ~BoundingBox();

    /** Copy Assignment Operator */
    const BoundingBox& operator= (const BoundingBox &boundingBox);    
};

struct FaceBodyBoundingBoxes {
    /** Bounding Boxes for Face and Body */
    BoundingBox face, body;

    /** 
     * Construct FaceBodyBoundingBoxes using bounding boxes
     * for face and body
     */
    FaceBodyBoundingBoxes(
        const BoundingBox &face_, 
        const BoundingBox &body_
    );

    /** Copy Constructor */
    FaceBodyBoundingBoxes(const FaceBodyBoundingBoxes &faceBody);

    /** Default Constructor */
    FaceBodyBoundingBoxes();
  
    /** Destructor */
    ~FaceBodyBoundingBoxes();

    /** Copy Assignment Operator */
    const FaceBodyBoundingBoxes& operator= (
        const FaceBodyBoundingBoxes &faceBody
    );
};

struct MatchedKeypoints {Position pos1, pos2;};

#endif
