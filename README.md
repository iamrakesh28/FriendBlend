# FriendBlend
FriendBlend is an application that merges two portraits of different people to create a single, multi-person photo. The 
protraits should have same background. The application is very useful when person A takes photo of person B, person B
takes photo of person A with the same background. The application produces a blended image having both persons in the 
image.
The application is implemented in C++ and the implementations depends on OpenCV liibrary.

## Run
Put the images int .. </br>
To run the application, type `make test_friendBlend`. </br>
These two images were blended together using the application to produce the following blended image.

## Working of the Application
There are four stpes involved behind the working algorithm of the application:
1. Color Correction
2. Face and Body Detection
3. Homography Estimation
    a. Keypoint Detection
    b. Keypoint Matching
    c. Computing the Homography
4. Image Blending
    a. Persons Far Apart : Alpha blending
    b. Persons Close Together : Grabcut
