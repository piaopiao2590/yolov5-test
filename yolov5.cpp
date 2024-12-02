#include "yolov5.h"
#include <fstream>
#include <QDebug>
#include <bitset>

yolov5::yolov5() {
    std::vector<std::string> class_list = load_class_list();

    // cv::Mat frame;


    bool is_cuda = true;
    int mark = 0;

    cv::dnn::Net net;
    load_net(net, is_cuda);

    std::vector<std::string> image_list;
    cv::glob("image/*.jpg", image_list);

    for (const auto& image_path : image_list)
    {
        frame = cv::imread(image_path);
        if (frame.empty())
        {
            std::cerr << "Could not read the image: " << image_path << std::endl;
            continue;
        }

        frame_pro = frame;

        std::vector<Detection> output;
        detect(frame, net, output, class_list);
        int detections = output.size();
        for (int i = 0; i < detections; ++i)
        {

            auto detection = output[i];
            auto confidence = detection.confidence;
            std::ostringstream oss;
            oss << std::fixed << std::setprecision(2) << confidence;
            auto box = detection.box;
            auto classId = detection.class_id;
            const auto color = colors[classId % colors.size()];
            cv::rectangle(frame, box, color, 3);

            int centreX = (box.x + box.width/2)/32;
            qDebug() << centreX;
            int centreY = (box.y + box.height/2)/5.5;
            uint64_t u64site = chage_64bit(centreX-1);
            qDebug() << u64site << "+" << centreY;
            u64_sites.push_back(u64site);
            distanceY.push_back(centreY);

            cv::rectangle(frame, cv::Point(box.x, box.y - 20), cv::Point(box.x + box.width, box.y), color, cv::FILLED);
            cv::putText(frame, class_list[classId].c_str() + oss.str() + "zuobiao:" + std::to_string(box.x + box.width / 2) + "," + std::to_string(box.y + box.height / 2), cv::Point(box.x, box.y - 5), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 0));
        }

        // qDebug() << frame.size().height << frame.size().width;
        cv::Mat resizeframe;
        cv::Size newSize(1360, 880);
        cv::resize(frame, resizeframe, newSize);
        // cv::imshow("output", resizeframe);

        // int k = cv::waitKey(1000);

        std::string output_folder = "image-mark";
        std::string output_filename = std::to_string(mark)+".jpg";
        cv::imwrite(output_folder + "/" + output_filename, frame);
        mark++;
    }


    cv::destroyAllWindows();

    std::cout << "OK "  << "\n";
}


vector<string> yolov5::load_class_list()
{
    std::vector<std::string> class_list;
    std::ifstream ifs("config_files/bottel.txt");
    std::string line;
    while (getline(ifs, line))
    {
        class_list.push_back(line);
    }
    return class_list;
}


void yolov5::load_net(cv::dnn::Net& net, bool is_cuda)
{
    auto result = cv::dnn::readNetFromONNX("config_files/best.onnx");
    if (is_cuda)
    {
        cout << "Attempty to use CUDA\n";
        result.setPreferableBackend(cv::dnn::DNN_BACKEND_CUDA);
        result.setPreferableTarget(cv::dnn::DNN_TARGET_CUDA_FP16);
    }
    else
    {
        cout << "Running on CPU\n";
        result.setPreferableBackend(cv::dnn::DNN_BACKEND_OPENCV);
        result.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);
    }
    net = result;
}

cv::Mat yolov5::format_yolov5(const cv::Mat& source) {
    int col = source.cols;
    int row = source.rows;
    int _max = MAX(col, row);
    cv::Mat result = cv::Mat::zeros(_max, _max, CV_8UC3);
    source.copyTo(result(cv::Rect(0, 0, col, row)));
    return result;
}

void yolov5::detect(cv::Mat& image, cv::dnn::Net& net, std::vector<Detection>& output, const std::vector<std::string>& className) {
    cv::Mat blob;

    auto input_image = format_yolov5(image);

    cv::dnn::blobFromImage(input_image, blob, 1. / 255., cv::Size(INPUT_WIDTH, INPUT_HEIGHT), cv::Scalar(), true, false);
    net.setInput(blob);
    std::vector<cv::Mat> outputs;
    net.forward(outputs, net.getUnconnectedOutLayersNames());

    float x_factor = input_image.cols / INPUT_WIDTH;
    float y_factor = input_image.rows / INPUT_HEIGHT;

    float* data = (float*)outputs[0].data;

    const int dimensions = 10;
    const int rows = 25200;

    std::vector<int> class_ids;
    std::vector<float> confidences;
    std::vector<cv::Rect> boxes;

    for (int i = 0; i < rows; ++i) {

        float confidence = data[4];
        if (confidence >= CONFIDENCE_THRESHOLD) {
            float* classes_scores = data + 5;
            cv::Mat scores(1, className.size(), CV_32FC1, classes_scores);
            cv::Point class_id;
            double max_class_score;
            minMaxLoc(scores, 0, &max_class_score, 0, &class_id);
            if (max_class_score > SCORE_THRESHOLD) {

                confidences.push_back(confidence);

                class_ids.push_back(class_id.x);

                float x = data[0];
                float y = data[1];
                float w = data[2];
                float h = data[3];
                int left = int((x - 0.5 * w) * x_factor);
                int top = int((y - 0.5 * h) * y_factor);
                int width = int(w * x_factor);
                int height = int(h * y_factor);
                boxes.push_back(cv::Rect(left, top, width, height));
            }

        }

        data += 10;

    }

    std::vector<int> nms_result;
    cv::dnn::NMSBoxes(boxes, confidences, SCORE_THRESHOLD, NMS_THRESHOLD, nms_result);
    for (int i = 0; i < nms_result.size(); i++) {
        int idx = nms_result[i];
        Detection result;
        result.class_id = class_ids[idx];
        result.confidence = confidences[idx];
        result.box = boxes[idx];
        output.push_back(result);
    }
}

uint64_t yolov5::chage_64bit(int num){
    bitset<64> result(0);
    result.set(num, true);
    if (num >0){
        result.set(num-1, true);
        if (num > 1){
            result.set(num-2, true);
        }
    }
    if (num < 63){
        result.set(num+1, true);
        if (num < 62){
            result.set(num+2, true);
        }
    }

    uint64_t rer = result.to_ullong();
    return rer;
}
