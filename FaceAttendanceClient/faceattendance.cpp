#include "faceattendance.h"
#include "ui_faceattendance.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/qsqlerror.h>
#include <QtSql/QSqlQuery>
#include <QBitmap>
#include <QDateTime>
#include <QDir>
#include <QPainter>

FaceAttendance::FaceAttendance(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FaceAttendence)
{
    ui->setupUi(this);
    ui->label->hide();
    ui->label_2->hide();
    ui->widget_2->hide();
    ui->head->setScaledContents(true);
    //启动摄像头
    cap.open(0);
    //启动定时器(在FaceAttendence内启动这个定时器后，每过100ms，会自动调用FaceAttendence的timerEvent)
    startTimer(100);
    //导入级联分类器文件
    cascade.load("D:/FaceRecognitionAttendanceSystem/opencv452/etc/haarcascades/haarcascade_frontalface_alt2.xml");

    mtimer.start(5000);
    connect(&mtimer,&QTimer::timeout,this,[this](){
        msocket.connectToHost(QHostAddress::LocalHost,9999);
        qDebug() << "正在连接服务器";
    });
    connect(&msocket,&QTcpSocket::connected,this,[this](){
        mtimer.stop();
        qDebug() << "成功连接服务器";
    });
    //为了防止与服务器的通信断开，这里设置信号槽实现重连
    connect(&msocket,&QTcpSocket::disconnected,this,[this](){
        mtimer.start(3000);
        qDebug() << "连接断开，即将重连";
    });

    //接受来自服务器的员工信息
    connect(&msocket,&QTcpSocket::readyRead,this,&FaceAttendance::recv_data);
}

FaceAttendance::~FaceAttendance()
{
    delete ui;
}

void FaceAttendance::timerEvent(QTimerEvent *e)
{
    //采集数据
    Mat srcImage;
    if(cap.grab()){
        cap.read(srcImage);
    }

    if(srcImage.data == nullptr) return;

    //检验人脸数据
    Mat grayImage;
    cv::cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);

    std::vector<Rect> faceRects;
    //使用灰度图提高检测速度
    cascade.detectMultiScale(grayImage, faceRects);
    if(faceRects.size() > 0){
        Rect rect = faceRects.at(0); // 第一个人脸矩形框
        ui->headpicLb->move(rect.x - 50, rect.y - 50); // 通过获得矩形框（未显示）的坐标，来移动实际识别圆圈的位置

        // 提取矩形框内的图像
        Mat faceImage = srcImage(rect);

        if(send_flag >= 0){
            if(send_flag > 2){
                // 把Mat数据转化成就jpg类型的字节流
                std::vector<uchar> buf;
                cv::imencode(".jpg", faceImage, buf);
                QByteArray byte((const char*)buf.data(), buf.size());
                // 将数据byte和其大小bytesize封装大另外一个QByteArray中并发送
                QByteArray sendData;
                QDataStream stream(&sendData, QIODevice::WriteOnly);
                stream.setVersion(QDataStream::Qt_5_14);
                quint64 bytesize = byte.size();
                stream << bytesize << byte;

                msocket.write(sendData);
                send_flag = -2;//发送一次人脸数据后不会再发送人脸数据，除非人脸框归位
                qDebug() << "发送了一次数据";

                cv::cvtColor(faceImage, faceImage, COLOR_BGR2RGB);//重新识别到人脸时会在头像框刷新人脸
                QImage image(faceImage.data, faceImage.cols, faceImage.rows, faceImage.step1(), QImage::Format_RGB888);
                QPixmap mmp = QPixmap::fromImage(image);

                ui->head->setPixmap(mmp);
            }
            send_flag++;
        }
    }
    if(faceRects.size() == 0){
        qDebug() << "人脸框归位";
        //人脸框归位
        ui->headpicLb->move(100, 60);
        send_flag = 0;
    }

    // 把opencv里面的Mat格式数据(BRG)转化成Qt里面的QImage格式数据（RGB）
    cv::cvtColor(srcImage, srcImage, COLOR_BGR2RGB);
    QImage image(srcImage.data, srcImage.cols, srcImage.rows, srcImage.step1(), QImage::Format_RGB888);
    QPixmap mmp = QPixmap::fromImage(image);
    ui->videoLb->setPixmap(mmp);
}

void FaceAttendance::recv_data()
{
    QString msg = msocket.readAll();
    qDebug() << msg;
    // 解析 JSON 数据
    QJsonDocument doc = QJsonDocument::fromJson(msg.toUtf8());

    QString employeeId;
    QString name;
    QString time;
    QString department;
    if (!doc.isNull()) {
        // 获取 JSON 对象
        QJsonObject jsonObj = doc.object();

        // 提取各个字段
        employeeId = jsonObj.value("employeeId").toString();
        name = jsonObj.value("name").toString();
        time = jsonObj.value("time").toString();
        department = jsonObj.value("department").toString();

        // 打印输出
        qDebug() << "Employee ID:" << employeeId;
        qDebug() << "Name:" << name;
        qDebug() << "Time:" << time;
    } else {
        qDebug() << "Invalid JSON format!";
    }
    ui->name->setText(name);
    ui->employeeid->setText(employeeId);
    ui->time->setText(time);
    ui->department->setText(department);

    if(ui->name->text().isEmpty()){
        qDebug() << "这时name是空的" <<ui->name->text();
        ui->label->hide();
        ui->label_2->hide();
        ui->widget_2->hide();
    }else{
        qDebug() << "name非空" <<ui->name->text();
        ui->label->show();
        ui->label_2->show();
        ui->widget_2->show();
    }
}

