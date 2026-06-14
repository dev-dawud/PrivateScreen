#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <iostream>
#include <vector>
#include <windows.h> //useed for LockWorkStation() function

class PrivateShoulderDetection {

public:

    void lockScreen(int personCount) {

        LockWorkStation();
    }

    void processing(cv::Mat& vid, cv::dnn::Net& net, std::vector<int>& indices, std::vector<cv::Rect>& boxes, std::vector<float>& confidences) {

        // convert input to a blob for the dnn module
        cv::Mat blob;

        cv::dnn::blobFromImage(vid, blob, 1.0 / 255.0, cv::Size(640, 640), cv::Scalar(), true, false);
        net.setInput(blob);

        // line 24 - line 56 is made with help of Gemini
        // list of output blobs
        std::vector<cv::Mat> outputs;

        net.forward(outputs, net.getUnconnectedOutLayersNames());

        // reshape the output to a 2D matrix
        cv::Mat output = outputs[0];
        cv::Mat rows = output.reshape(1, output.size[1]);

        cv::transpose(rows, rows);

        float conf_threshold = 0.5f;

        for (int i = 0; i < rows.rows; ++i) {

            float personScore = rows.at<float>(i, 4);

            if (personScore >= conf_threshold) {

                float cx = rows.at<float>(i, 0);
                float cy = rows.at<float>(i, 1);
                float w = rows.at<float>(i, 2);
                float h = rows.at<float>(i, 3);

                // find the top left corner of the bounding box and its width and height in pixel coordinates
                int left = static_cast<int>((cx - 0.5 * w) * vid.cols / 640.0);
                int top = static_cast<int>((cy - 0.5 * h) * vid.rows / 640.0);
                int width = static_cast<int>(w * vid.cols / 640.0);
                int height = static_cast<int>(h * vid.rows / 640.0);

                boxes.push_back(cv::Rect(left, top, width, height));
                confidences.push_back(personScore);
            }
        }

        // get rid of overlapping boxes
        cv::dnn::NMSBoxes(boxes, confidences, conf_threshold, 0.4f, indices);
    }

    void personCount(cv::Mat& vid, const std::vector<int>& indices, const std::vector<cv::Rect>& boxes) {

        int personCount = 0;

        for (int idx : indices) {

            personCount++;

            // red rectangle around detected person and label "Person"
            cv::rectangle(vid, boxes[idx], cv::Scalar(0, 0, 255), 2);

            cv::putText(vid, "Person", cv::Point(boxes[idx].x, boxes[idx].y - 5), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 255), 2);
  
        }

        // shows the number of detected people in the top left corner
        std::string status = "Persons in frame: " + std::to_string(personCount);
        cv::putText(vid, status, cv::Point(20, 40), cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(0, 255, 0), 2);

        if (personCount > 1) {

            lockScreen(personCount);
        }
    }

    void showWebcam(cv::dnn::Net& net) {

        cv::VideoCapture cap(0);
        cv::Mat vid;

        while (true) {

            cap.read(vid);

            if (vid.empty()) {
                std::cout << "waiting for webcam input..." << std::endl;
                continue;
            }

            cv::flip(vid, vid, 1);

            std::vector<int> indices;
            std::vector<cv::Rect> boxes;
            std::vector<float> confidences;


            processing(vid, net, indices, boxes, confidences);
            personCount(vid, indices, boxes);

            cv::imshow("webcam", vid);

            if (cv::waitKey(1) == 27) {
                break;
            }
        }
    }

};