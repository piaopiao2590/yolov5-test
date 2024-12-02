#ifndef YOLOV5_H
#define YOLOV5_H
#include <fstream>
#include <opencv2/opencv.hpp>


using namespace std;

class yolov5
{
public:
    const vector<cv::Scalar> colors = { cv::Scalar(255, 255, 0), cv::Scalar(0, 255, 0), cv::Scalar(0, 255, 255), cv::Scalar(255, 0, 0) };
    vector<uint64_t> u64_sites;
    vector<int> distanceY;

    const float INPUT_WIDTH = 640.0;
    const float INPUT_HEIGHT = 640.0;
    const float SCORE_THRESHOLD = 0.2;
    const float NMS_THRESHOLD = 0.45;
    const float CONFIDENCE_THRESHOLD = 0.1;

    cv::Mat frame;
    cv::Mat frame_pro;

    struct Detection
    {
        int class_id;
        float confidence;
        cv::Rect box;
    };



    yolov5();
    uint64_t chage_64bit(int num);
    vector<string> load_class_list();
    void load_net(cv::dnn::Net& net, bool is_cuda);
    cv::Mat format_yolov5(const cv::Mat& source);
    void detect(cv::Mat& image, cv::dnn::Net& net, std::vector<Detection>& output, const std::vector<std::string>& className);
};

#endif // YOLOV5_H
