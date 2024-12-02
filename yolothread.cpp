#include "yolothread.h"

YoloThread::YoloThread(QObject *parent)
    : QThread{parent}
{
    yolo = new Yolo_Test;
    isstop = false;
    isconnect = false;
    tcpbus = new Modbus;
}

void YoloThread::run(){

    std::vector<std::string> image_list;
    cv::glob("image/*.jpg", image_list);

    static int i = 0;
    while (!isstop){
        // for (const auto& image_path : image_list){
        //     image = cv::imread(image_path);
        //     // cv::imshow("image_show", image);
        //     // cv::waitKey(1000);
        //     yolo->open_camera(image);
        //     emit dealsignal();
        // }

        const auto& image_path = image_list[i];
        i++;
        image = cv::imread(image_path);

        emit dealimage();

        yolo->open_camera(image);
        yoloimg = yolo->img;
        emit dealsignal();
        if (i >= image_list.size()){
            i = 0;
        }

        if (isconnect){
            vector<uint32_t> yu32_sites = yolo->u32_sites;
            vector<int> ydistanceY = yolo->distanceY;
            tcpbus->sendmessage(ydistanceY[0], yu32_sites[0], yu32_sites[1]);
        }
    }

}

void YoloThread::setflag(bool flag){
    isstop = flag;
}

void YoloThread::getimage(cv::Mat &img){
    img = image;
}

void YoloThread::getyoloimage(cv::Mat &img){
    img = yoloimg;
}

void YoloThread::setipaddress(const QString &ip){
    isconnect = true;
    ipaddress = ip;
    tcpbus->connectIP(ipaddress);
}

void YoloThread::disconnect(){
    isconnect = false;
    tcpbus->discon();
}
