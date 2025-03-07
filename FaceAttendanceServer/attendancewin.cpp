#include "attendancewin.h"
#include "ui_attendancewin.h"
#include <vector>
#include <qsqlquery.h>
#include <qsqlerror.h>
#include <QDateTime>
#include <QThread>

using namespace std;

AttendanceWin::AttendanceWin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AttendanceWin)
{
    ui->setupUi(this);

    bsize = 0;
    //开始监听
    mserver.listen(QHostAddress::Any,9999);
    //处理新连接
    connect(&mserver,&QTcpServer::newConnection,this,[this](){
        //获取与客户端通信的套接字
        msocket = mserver.nextPendingConnection();
        connect(msocket,&QTcpSocket::readyRead,this,&AttendanceWin::read_data);
    });

    QThread *thread = new QThread();
    fobject.moveToThread(thread);
    thread->start();
    connect(this,&AttendanceWin::query,&fobject,&QFaceObject::face_query);

    connect(&fobject,&QFaceObject::send_faceid,this,&AttendanceWin::recv_faceid);
}

AttendanceWin::~AttendanceWin()
{
    delete ui;
}

void AttendanceWin::read_data()
{
    //创建数据流
    QDataStream stream(msocket);
    stream.setVersion(QDataStream::Qt_5_14);

    if(bsize==0){
        if(msocket->bytesAvailable() < (qint64)sizeof(bsize))return;

        //采集数据的长度
        stream>>bsize;
    }

    //由bsize判断是否可以读取数据
    if(msocket->bytesAvailable() < (qint64)bsize)return;
    QByteArray data;
    stream>>data;

    //bsize清零
    bsize = 0;

    QPixmap mmp;
    mmp.loadFromData(data,".jpg");
    mmp = mmp.scaled(ui->picLb->size());
    ui->picLb->setPixmap(mmp);


    //识别人脸
    cv::Mat faceImage;
    vector<uchar> buf;
    buf.assign(data.begin(),data.end());
    faceImage = cv::imdecode(buf,cv::IMREAD_COLOR);
    if (faceImage.empty()) {
        qDebug() << "无法解码图像数据";
    } else {
        qDebug() << "图像解码成功";
    }

//    int faceId = fobject.face_query(faceImage);//消耗资源较多
    emit query(faceImage);
}

void AttendanceWin::recv_faceid(int64_t faceId)
{
    QString sdmsg;
    qDebug() << "此人的faceId是：" << faceId;
    if(faceId<0){
        sdmsg = QString("{\"employeeId\":\"\",\"name\":\"\",\"department\":\"\",\"time\":\"\"}");
        msocket->write(sdmsg.toUtf8());
        return;
    }

    //从server.db数据库查询此faceId的相关信息
    QSqlQuery query;
    query.prepare("select employeeId,name from employee where faceId =:faceId");
    query.bindValue(":faceId",faceId);

    int employeeId;
    QString name;
    if (query.exec()) {
        if (query.next()) {  // 如果有结果
            employeeId = query.value(0).toInt();  // 获取 id
            name = query.value(1).toString();  // 获取 age
            qDebug() << "employeeId:" << employeeId << ", name:" << name;
        } else {
            qDebug() << "没有找到faceId为" << faceId << "的记录";
        }
    } else {
        qDebug() << "查询失败：" << query.lastError().text();
    }

    sdmsg = QString("{\"employeeId\":\"%1\",\"name\":\"%2\",\"department\":\"软件\",\"time\":\"%3\"}")
                        .arg(QString::number(employeeId))
                        .arg(name)
                        .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    qDebug() << sdmsg;
    msocket->write(sdmsg.toUtf8());

    query.prepare("insert into attendance(employeeId) values(:employeeId)");
    query.bindValue(":employeeId",employeeId);
    if(query.exec()){
        qDebug() << "attendance表插入成功";
    }else{
        qDebug() << "attendance表插入失败";
        qDebug() << query.lastError().text();
    }
}

