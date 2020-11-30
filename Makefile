

CPP_FLAGS=`pkg-config --cflags --libs opencv4` -std=c++11 -I src


# Tests

# Process

# Contrast Stretching
test_process_constrastStretch: src/process/process.cpp src/test/process/constrastStretchTest.cpp
	echo ${CPP_FLAGS}
	g++ ${CPP_FLAGS} src/process/process.cpp src/test/process/constrastStretchTest.cpp -o bin/constrastStretchTest
	./bin/constrastStretchTest

# Histogram Equalize
test_process_histogramEqualize: src/process/process.cpp src/test/process/histogramEqualizeTest.cpp
	g++ ${CPP_FLAGS} src/process/process.cpp src/test/process/histogramEqualizeTest.cpp -o bin/histogramEqualizeTest
	./bin/histogramEqualizeTest

# CLAHE
test_process_claheTest: src/process/process.cpp src/test/process/claheTest.cpp
	g++ ${CPP_FLAGS} src/process/process.cpp src/test/process/claheTest.cpp -o bin/claheTest
	./bin/claheTest

# Color Correction

