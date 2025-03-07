#ifndef FACEATTENDENCE_H
#define FACEATTENDENCE_H

#include <QMainWindow>
#include <opencv.hpp>
using namespace cv;
using namespace std; 
#include <QTcpSocket>
#include <QTimer>
#include <QHostAddress>

QT_BEGIN_NAMESPACE
namespace Ui { class FaceAttendence; }
QT_END_NAMESPACE

class FaceAttendance : public QMainWindow
{
    Q_OBJECT

public:
    FaceAttendance(QWidget *parent = nullptr);
    ~FaceAttendance();

    void timerEvent(QTimerEvent *e);
private slots:
    void recv_data();
private:
    Ui::FaceAttendence *ui;
    
    //opencv摄像头工具
    cv::VideoCapture cap;
    //级联分类器
    cv::CascadeClassifier cascade;

    //创建网络套接字，定时器
    QTcpSocket msocket;
    QTimer mtimer;

    int send_flag = -1;//控制人脸发送速度
};
#endif // FACEATTENDENCE_H
