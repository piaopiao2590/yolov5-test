#include "widget.h"
#include "ui_widget.h"
#include <opencv2/opencv.hpp>
#include <QCloseEvent>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    yothread = new YoloThread(this);
    connect(yothread, &YoloThread::dealsignal, this, &Widget::dealSignal);
    connect(yothread, &YoloThread::dealimage, this, &Widget::dealImage);
    layout = new QVBoxLayout(ui->imageorginGB);

    imageorginLb = new QLabel(ui->imageorginGB);

    layout2 = new QVBoxLayout(ui->imageyoloGB);

    imageyoloLb = new QLabel(ui->imageyoloGB);
    // displayImage(yolo->frame_pro);
    // displayImage_yolo(yolo->frame);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_runpB_clicked()
{
    yothread->setflag(false);
    yothread->start();
}


void Widget::on_stoppB_clicked()
{
    yothread->setflag(true);
    yothread->quit();
    yothread->wait();
}

void Widget::dealSignal(){
    yothread->getyoloimage(yoloimg);
    QImage fra = matTOImage(yoloimg);
    fra = fra.scaled(320, 160, Qt::KeepAspectRatio, Qt::SmoothTransformation);


    layout2->addWidget(imageyoloLb);
    // ui->imageorginGB->setLayout(layout);
    imageyoloLb->setPixmap(QPixmap::fromImage(fra));

}

void Widget::dealImage(){
    yothread->getimage(img);
    QImage fra = matTOImage(img);
    fra = fra.scaled(320, 160, Qt::KeepAspectRatio, Qt::SmoothTransformation);


    layout->addWidget(imageorginLb);
    // ui->imageorginGB->setLayout(layout);
    imageorginLb->setPixmap(QPixmap::fromImage(fra));

}

void Widget::closeEvent(QCloseEvent *event){
    if (yothread->isRunning() == false){
        return;
    }

    yothread->setflag(true);
    yothread->quit();
    yothread->wait();
    event->accept();
}

QImage Widget::matTOImage(const cv::Mat &inmat){
    QImage image(inmat.data, inmat.cols, inmat.rows, static_cast<int>(inmat.step), QImage::Format_RGB888);
    return image.rgbSwapped();
}



void Widget::on_connectIP_clicked()
{
    if (ui->connectIP->text() == nullptr){
        qDebug() << "请输入ip";
    }
    else{
        QString ipaddress = ui->ipaddress->text();
        yothread->setipaddress(ipaddress);
        }
}


void Widget::on_disconnect_clicked()
{
    yothread->disconnect();
}

