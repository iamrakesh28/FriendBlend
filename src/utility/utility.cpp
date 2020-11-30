#include <opencv2/core/types.hpp>
#include <utility/utility.hpp>

/** Position */

Position::Position(int r_, int c_):
    r(r_), c(c_) {}

Position::Position(const Position &pos):
    r(pos.r), c(pos.c) {}

Position::~Position() {}

const Position& Position::operator= (const Position &pos) {
    r = pos.r, c = pos.c;
    return *this;
}

Position::operator cv::Point() {
    return cv::Point(c, r);
}

/** BoundingBox */

BoundingBox::BoundingBox(
    const Position &topLeft_, 
    const Position &bottomRight_
):
    topLeft(topLeft_), bottomRight(bottomRight_) {}

BoundingBox::BoundingBox(const BoundingBox &boundingBox):
    topLeft(boundingBox.topLeft),
    bottomRight(boundingBox.bottomRight) {}

BoundingBox::~BoundingBox() {}

const BoundingBox& BoundingBox::operator= (const BoundingBox &boundingBox) {
    topLeft = boundingBox.topLeft;
    bottomRight = boundingBox.bottomRight;
    return *this;
}

/** FaceBodyBoundingBoxes */

FaceBodyBoundingBoxes::FaceBodyBoundingBoxes(
    const BoundingBox &face_, 
    const BoundingBox &body_
):
    face(face_), body(body_) {}

FaceBodyBoundingBoxes::FaceBodyBoundingBoxes(
    const FaceBodyBoundingBoxes &faceBody
):
    face(faceBody.face), body(faceBody.body) {}

FaceBodyBoundingBoxes::~FaceBodyBoundingBoxes() {}

const FaceBodyBoundingBoxes& FaceBodyBoundingBoxes::operator= (
    const FaceBodyBoundingBoxes &faceBody
) {
    face = faceBody.face;
    body = faceBody.body;
    return *this;
}
