#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include "detection.h"

int main() {

	PrivateShoulderDetection psd;

    // for Person detection
    cv::dnn::Net net = cv::dnn::readNetFromONNX("yolov8n.onnx");

    if (net.empty()) {
        std::cerr << "could not load model!" << std::endl;
        return -1;
    }

    psd.showWebcam(net);

    return 0;
}