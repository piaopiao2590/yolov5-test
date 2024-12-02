#ifndef YOLOTHREAD_H
#define YOLOTHREAD_H

#include <QObject>
#include <yolo_test.h>
#include <opencv2/opencv.hpp>
#include <QThread>
#include <modbus.h>

class YoloThread : public QThread
{
    Q_OBJECT
public:
    explicit YoloThread(QObject *parent = nullptr);
    void setflag(bool flag);
    void getimage(cv::Mat &img);
    void getyoloimage(cv::Mat &img);
    void setipaddress(const QString &ip);
    void disconnect();

protected:
    void run();

private:
    Yolo_Test *yolo;
    cv::Mat image;
    bool isstop;
    cv::Mat yoloimg;
    QString ipaddress;
    Modbus *tcpbus;
    bool isconnect;

signals:
    void dealsignal();
    void dealimage();
};

#endif // YOLOTHREAD_H
