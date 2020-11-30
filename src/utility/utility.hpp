#ifndef UTILITY_HPP
#define UTILITY_HPP

struct Position {
    int r, c;

    Position(int r_, int c_):
        r(r_), c(c_) {}

    Position(const Position &pos):
        r(pos.r), c(pos.c) {}

    ~Position() {}

    const Position& operator= (const Position &pos) {
        r = pos.r, c = pos.c;
        return *this;
    }
};

struct BoundingBox {
    Position topLeft, bottomRight;

    BoundingBox(
        const Position &topLeft_, 
        const Position &bottomRight_
    ):
        topLeft(topLeft_), bottomRight(bottomRight_) {}

    BoundingBox(const BoundingBox &boundingBox):
        topLeft(boundingBox.topLeft),
        bottomRight(boundingBox.bottomRight) {}

    const BoundingBox& operator= (const BoundingBox &boundingBox) {
        topLeft = boundingBox.topLeft;
        bottomRight = boundingBox.bottomRight;
        return *this;
    }

    ~BoundingBox() {}
};

struct FaceBodyBoundingBoxes {
    BoundingBox face, body;

    FaceBodyBoundingBoxes(
        const BoundingBox &face_, 
        const BoundingBox &body_
    ):
        face(face_), body(body_) {}

    FaceBodyBoundingBoxes(const FaceBodyBoundingBoxes &faceBody):
        face(faceBody.face), body(faceBody.body) {}

    const FaceBodyBoundingBoxes& operator= (
        const FaceBodyBoundingBoxes &faceBody
    ) {
        face = faceBody.face;
        body = faceBody.body;
        return *this;
    }

    ~FaceBodyBoundingBoxes() {}
};

struct MatchedKeypoints {Position pos1, pos2;};

#endif
