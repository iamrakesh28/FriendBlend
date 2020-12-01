# FriendBlend
FriendBlend is an application that merges two portraits of different people to create a single, multi-person photo. The 
protraits should have same background. The application is very useful when person A takes photo of person B, person B
takes photo of person A with the same background. The application produces a blended image having both persons in the 
image. </br>
The application is implemented in C++ and the implementations depends on OpenCV liibrary.

## Run
Put the images int .. </br>
To run the application, type `make test_friendBlend`. </br>
These two images were blended together using the application to produce the following blended image.

## Working of the Application
There are four stpes involved behind the working algorithm of the application:
###  1. Color Correction
Before the blending process, the lighting from the two input images should be approximately the same otherwise
the blended image could have some artifacts. We perform histogram equalization on both the images for the color 
correction.
    
### 2. Face and Body Detection
We have two image merging process : Alpha blending and Grabcut. Depending on the location of the humans, one of
the image merging or blending chosen. To find the location of the human, we detect the face and get the bounding
box using Haar Cascade models in OpenCV. From the face bounding box, we estimate the bounding box for the human body.
    
3. Homography Estimation

    a. Keypoint Detection
    b. Keypoint Matching
    c. Computing the Homography
4. Image Blending
    a. Persons Far Apart : Alpha blending
    b. Persons Close Together : Grabcut
