#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>
#include "process/process.hpp"

#include <iostream>
using namespace std;

using namespace cv;

struct MinMax {
    Vec3b minValues, maxValues;
};

Vec3b min(Vec3b u, Vec3b v) {
    return Vec3b(
        min(u[0], v[0]),
        min(u[1], v[1]),
        min(u[2], v[2])
    );
} 

Vec3b max(Vec3b u, Vec3b v) {
    return Vec3b(
        max(u[0], v[0]),
        max(u[1], v[1]),
        max(u[2], v[2])
    );
} 

MinMax getMinMax(const Mat &img) {
    MinMax minMax;
    minMax.minValues = Vec3b(255, 255, 255);
    minMax.maxValues = Vec3b(0, 0, 0);

    for(int r = 0;r < img.rows;r++) {
        for(int c = 0;c < img.cols;c++) {
            minMax.minValues = min(minMax.minValues, img.at<Vec3b>(r, c));
            minMax.maxValues = max(minMax.maxValues, img.at<Vec3b>(r, c));
        }
    }

    return minMax;
}

void contrastStretchIndependent(Mat &img) {
    MinMax minMax = getMinMax(img);
    double diff[3];
    for(int channel = 0;channel < 3;channel++)
        diff[channel] = static_cast<double>(minMax.maxValues[channel])
            - static_cast<double>(minMax.minValues[channel]);

    for(int r = 0;r < img.rows;r++) {
        for(int c = 0;c < img.cols;c++) {
            Vec3b pixel = img.at<Vec3b>(r, c);

            for(int channel = 0;channel < 3;channel++) {
                if(diff[channel] != 0) {
                    double channelValue = static_cast<double>(pixel[channel]);
                    
                    channelValue = 
                        255.0 * (channelValue - minMax.minValues[channel]) / diff[channel];

                    img.at<Vec3b>(r, c)[channel] = static_cast<uchar>(channelValue);
                }
            }
        }
    }
}

void contrastStretchY(Mat &img) {
    cvtColor(img, img, COLOR_BGR2YCrCb);

    MinMax minMax = getMinMax(img);
    double minValue = minMax.minValues[0];
    double diff = static_cast<double>(minMax.maxValues[0])
        - static_cast<double>(minMax.minValues[0]);

    if(diff != 0) {
        for(int r = 0;r < img.rows;r++) {
            for(int c = 0;c < img.cols;c++) {
                double value = static_cast<double>(img.at<Vec3b>(r, c)[0]);
            
                value = 255.0 * (value - minValue) / diff;

                img.at<Vec3b>(r, c)[0] = static_cast<uchar>(value);
            }
        }
    }

    cvtColor(img, img, COLOR_YCrCb2BGR);
}

void contrastStretch(Mat &img, ContrastStretchMethod method) {
    if(method == EACH_CHANNEL_INDEPENDENT)
        contrastStretchIndependent(img);
    else
        contrastStretchY(img);
}

void histogramEqualize(Mat &img) {
    cvtColor(img, img, COLOR_BGR2YCrCb);

    Range yChannelRange[] = {
        Range::all(),
        Range::all(),
        Range(0, 1)
    };

    equalizeHist(img(yChannelRange), img(yChannelRange));
    cvtColor(img, img, COLOR_YCrCb2BGR);
}
