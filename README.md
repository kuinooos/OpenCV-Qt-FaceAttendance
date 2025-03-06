# OpenCV-Qt-FaceAttendance
人脸识别考勤系统是一个高效、智能的考勤管理解决方案，通过结合客户端和服务端的功能，实现了员工信息注册、人脸图像采集与识别、考勤记录管理等功能。系统采用先进的人脸识别技术，提高了考勤的准确性和效率，减少了人工操作的繁琐和错误。
# 人脸识别考勤系统服务端 - AttendanceWin模块说明

## 一、概述
本项目是一个基于人脸识别技术的考勤系统的服务端部分，`attendancewin.cpp` 文件实现了考勤窗口的核心功能，包括监听客户端连接、接收客户端发送的人脸图像、进行人脸识别、查询员工信息并记录考勤等操作。

## 二、功能特性
1. **网络监听**：服务端通过 `QTcpServer` 监听端口 `9999`，等待客户端的连接请求。
2. **数据接收**：当有客户端连接并发送数据时，服务端接收数据并进行解码，将人脸图像显示在界面上。
3. **人脸识别**：调用 `QFaceObject` 类的 `face_query` 方法对人脸图像进行识别，获取对应的 `faceId`。
4. **员工信息查询**：根据 `faceId` 从 `server.db` 数据库的 `employee` 表中查询员工的基本信息。
5. **考勤记录**：将识别成功的员工的考勤信息插入到 `server.db` 数据库的 `attendance` 表中。

## 三、代码结构

### 1. 类定义
`AttendanceWin` 类继承自 `QMainWindow`，是考勤窗口的主要类，包含以下主要成员：
- `mserver`：`QTcpServer` 对象，用于监听客户端连接。
- `msocket`：`QTcpSocket` 对象，用于与客户端进行通信。
- `fobject`：`QFaceObject` 对象，用于进行人脸识别。

### 2. 构造函数 `AttendanceWin::AttendanceWin(QWidget *parent)`
- 初始化界面。
- 开始监听端口 `9999`。
- 处理新的客户端连接，连接信号槽以便在有数据可读时调用 `read_data` 方法。
- 将 `fobject` 移动到新线程中运行，提高性能。
- 连接信号槽，将 `query` 信号连接到 `QFaceObject` 的 `face_query` 方法，将 `QFaceObject` 的 `send_faceid` 信号连接到 `recv_faceid` 方法。

### 3. 析构函数 `AttendanceWin::~AttendanceWin()`
释放界面资源。

### 4. 数据接收方法 `AttendanceWin::read_data()`
- 通过 `QDataStream` 从客户端接收数据。
- 解码接收到的数据，将人脸图像显示在界面上。
- 调用 `query` 信号触发人脸识别。

### 5. 人脸识别结果处理方法 `AttendanceWin::recv_faceid(int64_t faceId)`
- 根据 `faceId` 从数据库中查询员工信息。
- 将查询到的员工信息封装成 JSON 格式的字符串发送给客户端。
- 将考勤信息插入到 `attendance` 表中。

## 四、使用方法

### 1. 环境准备
- 确保已经安装了 Qt 开发环境。
- 确保已经安装了 OpenCV 和 SeetaFace 库。

### 2. 数据库准备
- 运行 `main.cpp` 中的代码，创建 `server.db` 数据库，并创建 `employee` 和 `attendance` 表。

### 3. 编译和运行
- 使用 Qt Creator 打开项目，编译并运行服务端程序。
- 启动客户端程序，客户端连接到服务端的 `9999` 端口并发送人脸图像数据。

### 4. 注意事项
- 确保服务端和客户端的网络连接正常。
- 确保数据库文件 `server.db` 存在且可读写。

## 五、代码示例
```cpp
// 构造函数部分
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

// 数据接收方法部分
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

    emit query(faceImage);
}

// 人脸识别结果处理方法部分
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
