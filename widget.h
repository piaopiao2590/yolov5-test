#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <yolothread.h>
#include <opencv2/opencv.hpp>
#include <QVBoxLayout>
#include <QLabel>


QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    void displayImage(cv::Mat image);
    void displayImage_yolo(cv::Mat image);
    QImage matTOImage(const cv::Mat &inmat);
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_runpB_clicked();

    void on_stoppB_clicked();

    void dealSignal();
    void dealImage();

    void on_connectIP_clicked();

    void on_disconnect_clicked();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::Widget *ui;
    YoloThread *yothread;
    cv::Mat img;
    cv::Mat yoloimg;
    QVBoxLayout *layout;
    QLabel *imageorginLb;
    QVBoxLayout *layout2;
    QLabel *imageyoloLb;

};
#endif // WIDGET_H
