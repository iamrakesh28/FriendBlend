
CPP_FLAGS=`pkg-config --cflags --libs opencv4` -std=c++11 -I src


# Tests

# Process

# Contrast Stretching
test_process_constrastStretch: src/process/process.cpp src/test/process/constrastStretchTest.cpp
	echo ${CPP_FLAGS}
	g++ src/process/process.cpp src/test/process/constrastStretchTest.cpp -o bin/constrastStretchTest ${CPP_FLAGS}
	./bin/constrastStretchTest

# Histogram Equalize
test_process_histogramEqualize: src/process/process.cpp src/test/process/histogramEqualizeTest.cpp
	g++ src/process/process.cpp src/test/process/histogramEqualizeTest.cpp -o bin/histogramEqualizeTest ${CPP_FLAGS}
	./bin/histogramEqualizeTest

# CLAHE
test_process_clahe: src/process/process.cpp src/test/process/claheTest.cpp
	g++ src/process/process.cpp src/test/process/claheTest.cpp -o bin/claheTest ${CPP_FLAGS}
	./bin/claheTest

# Color Correction

# Histogram Equalize
test_colorCorrect_histogramEqualize: src/process/process.cpp src/colorCorrect/histogramEqualizeMethod.cpp src/test/colorCorrect/histogramEqualizeMethod.cpp
	g++ src/process/process.cpp src/colorCorrect/histogramEqualizeMethod.cpp src/test/colorCorrect/histogramEqualizeMethod.cpp -o bin/histogramEqualizeMethod ${CPP_FLAGS}
	./bin/histogramEqualizeMethod

# CLAHE
test_colorCorrect_clahe: src/process/process.cpp src/colorCorrect/claheMethod.cpp src/test/colorCorrect/claheMethod.cpp
	g++ src/process/process.cpp src/colorCorrect/claheMethod.cpp src/test/colorCorrect/claheMethod.cpp -o bin/claheMethod ${CPP_FLAGS}
	./bin/claheMethod

# Face Body Detection

# Haar Cascade
test_faceBodyDetect_haarCascade: src/process/process.cpp src/utility/utility.cpp src/faceBodyDetect/haarCascade.cpp src/test/faceBodyDetect/haarCascadeTest.cpp
	g++ src/process/process.cpp src/utility/utility.cpp src/faceBodyDetect/haarCascade.cpp src/test/faceBodyDetect/haarCascadeTest.cpp -o bin/haarCascadeTest ${CPP_FLAGS}
	./bin/haarCascadeTest
