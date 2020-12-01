
CPP_FLAGS=`pkg-config --cflags --libs opencv4` -std=c++11 -I src

Req=src/utility/utility.cpp src/process/process.cpp src/colorCorrect/claheMethod.cpp src/colorCorrect/histogramEqualizeMethod.cpp src/faceBodyDetect/haarCascade.cpp src/align/align.cpp src/blend/blend.cpp src/friendBlend/friendBlend.cpp

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

# Align
test_align: src/utility/utility.cpp src/align/align.cpp src/faceBodyDetect/haarCascade.cpp src/test/align/alignTest.cpp
	g++ src/utility/utility.cpp src/align/align.cpp src/faceBodyDetect/haarCascade.cpp src/test/align/alignTest.cpp -o bin/alignTest ${CPP_FLAGS}
	./bin/alignTest

# Blend

test_blend: src/utility/utility.cpp src/blend/blend.cpp src/faceBodyDetect/haarCascade.cpp src/test/blend/blendTest.cpp
	g++ src/utility/utility.cpp src/blend/blend.cpp src/faceBodyDetect/haarCascade.cpp src/test/blend/blendTest.cpp -o bin/blendTest ${CPP_FLAGS}
	./bin/blendTest

# Friend Blend

test_friendBlend: ${Req} src/test/friendBlend/friendBlendTest.cpp
	g++ ${Req} src/test/friendBlend/friendBlendTest.cpp -o bin/friendBlendTest ${CPP_FLAGS}
	./bin/friendBlendTest
