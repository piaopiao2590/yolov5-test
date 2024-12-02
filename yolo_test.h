#ifndef YOLO_TEST_H
#define YOLO_TEST_H

#include <fstream>
#include <opencv2/opencv.hpp>

using namespace std;

class Yolo_Test
{
public:
    const vector<cv::Scalar> colors = { cv::Scalar(255, 255, 0), cv::Scalar(0, 255, 0), cv::Scalar(0, 255, 255), cv::Scalar(255, 0, 0) };
    vector<uint32_t> u32_sites;
    vector<int> distanceY;
    cv::Mat img;

    const float INPUT_WIDTH = 640.0;
    const float INPUT_HEIGHT = 640.0;
    const float SCORE_THRESHOLD = 0.2;
    const float NMS_THRESHOLD = 0.45;
    const float CONFIDENCE_THRESHOLD = 0.1;
    int mark;
    bool is_cuda;
    std::vector<std::string> class_list;
    int nRet;
    cv::dnn::Net net;

    // cv::Mat frame;
    cv::Mat frame_pro;

    struct Detection
    {
        int class_id;
        float confidence;
        cv::Rect box;
    };



    Yolo_Test();
    void open_camera(cv::Mat frame);
    uint64_t chage_64bit(int num);
    vector<string> load_class_list();
    void load_net(cv::dnn::Net& net, bool is_cuda);
    cv::Mat format_yolov5(const cv::Mat& source);
    void detect(cv::Mat& image, cv::dnn::Net& net, std::vector<Detection>& output, const std::vector<std::string>& className);
    uint32_t chage_32bit(int num);


private:

};

#endif // YOLO_TEST_H
