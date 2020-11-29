#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>
#include "process/process.hpp"

using namespace cv;

void contrastStretch(Mat &img) {
    cvtColor(img, img, COLOR_RGB2YCrCb);

    Range yChannelRange[] = {
        Range::all(),
        Range::all(),
        Range(0, 1)
    };

    yChannelImg = img(yChannelRange);

    double minValue, maxValue, diff;
    minMaxLoc(yChannelImg, &minValue, &maxValue);
    diff = maxValue - minValue;

    if(diff != 0) {
        for(int r = 0;r < yChannelRange.size[0];r++) {
            for(int c = 0;c < yChannelRange.size[1];c++) {
                double value = static_cast<double>(yChannelImg.at<uchar>(r, c));
                value *= 255.0 / diff;

                yChannelImg.at<uchar>(r, c) = static_cast<uchar>(value);
            }
        }
    }

    equalizeHist(img(yChannelRange), img(yChannelRange));
    cvtColor(img, img, COLOR_YCrCb2RGB);
}

void histogramEqualize(Mat &img) {
    cvtColor(img, img, COLOR_RGB2YCrCb);

    Range yChannelRange[] = {
        Range::all(),
        Range::all(),
        Range(0, 1)
    };

    equalizeHist(img(yChannelRange), img(yChannelRange));
    cvtColor(img, img, COLOR_YCrCb2RGB);
}
