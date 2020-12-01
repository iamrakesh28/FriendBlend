# Source Directory
It contains all the C++ source code of the FriendBlend application.

## Directory Structure
```
src/
|__ utility/
|    |__ utility.hpp
|    |__ utility.cpp
|   
|__ process/
|    |__ process.hpp
|    |__ process.cpp
| 
|__ colorCorrect/
|    |__ colorCorrect.hpp
|    |__ colorCorrection.cpp
|    |__ claheMethod.hpp
|    |__ claheMethod.cpp
|    |__ histogramEqualizeMethod.hpp
|    |__ histogramEqualizeMethod.cpp
|
|__ faceBodyDetect/
|    |__ faceBodyDetect.hpp
|    |__ faceBodyDetection.hpp
|    |__ haarCascade.hpp
|    |__ haarCascade.cpp
|
|__ align/
|    |__ align.hpp
|    |__ align.cpp
|
|__ blend/
|    |__ blend.hpp
|    |__ blend.cpp
|
|__ friendBlend/
|    |__ friendBlend.hpp
|    |__ friendBlend.cpp
|
|__ imgLog/
|    |__ imgLog.hpp
|    |__ imgLog.cpp
|
|__ test/
```

* ```utility/```  </br>
Defines some utility class such as Position, BoundingBox, etc.
* ```process/```  </br>
Defines some image processing algorithms like histogram equalization, clahe, etc.
* ```colorCorrect/```  </br>
Source code for different color correction algorithms are stored
* ```faceBodyDetect/```  </br>
Contains the face detection algorithms code
* ```align/``` </br>
Source code for keypoint detection, keypoint matching and finding homography is stored
* ```blend/``` </br>
Stores Blending algorithm source code
* ```friendBlend/``` </br>
Implements the friendBlend algorithm using the above algorithms
* ```imgLog/``` </br>
Implements the logger for the application
* ```test/``` </br> 
Contains codes for testing each algorithm as well as the application

