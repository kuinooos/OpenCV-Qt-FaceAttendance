#include "registerwin.h"
#include "ui_registerwin.h"
#include <QSqlQuery>
#include <QSqlError>

RegisterWin::RegisterWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegisterWin)
{
    ui->setupUi(this);

    QDir dir;
    if (!dir.exists("./data")) {
        if (dir.mkdir("./data")) {
            qDebug() << "data文件夹创建成功";
        } else {
            qDebug() << "data文件夹创建失败";
        }
    }

    timerid = 0;
}

RegisterWin::~RegisterWin()
{
    delete ui;
}

void RegisterWin::timerEvent(QTimerEvent *event)
{
    // 检查摄像头是否成功打开
    if (!cap.isOpened()) {
        std::cerr << "摄像头打开失败" << std::endl;
        return;
    }

    cap>>image;
    if(image.data==nullptr)return;

    //Mat --> QImage
    cv::Mat rgbMat;
    cv::cvtColor(image,rgbMat,cv::COLOR_BGR2RGB);//先将BGR的mat转化为RGB的mat
    QImage img(rgbMat.data,rgbMat.cols,rgbMat.rows,rgbMat.step1(),QImage::Format_RGB888);

    //显示在头像框
    QPixmap mmp = QPixmap::fromImage(img);
    mmp = mmp.scaled(img.width(),img.height());
    ui->headPb->setPixmap(mmp);
}

void RegisterWin::on_resetPb_clicked()
{
    ui->nameEdit->clear();
    ui->addressEdit->clear();
    ui->phoneEdit->clear();
    ui->birthDEdit->setDate(QDate::currentDate());
    ui->picpathEdit->clear();
    ui->headPb->clear();
}


void RegisterWin::on_addheadPb_clicked()
{
    QString filepath = QFileDialog::getOpenFileName(this);
    ui->picpathEdit->setText(filepath);

    QPixmap mmp(filepath);
    mmp = mmp.scaledToWidth(ui->headPb->width());
    ui->headPb->setPixmap(mmp);
}

void RegisterWin::on_registerPb_clicked()
{
    // 1. 通过照片，结合faceObject模块得到faceID
    QFaceObject faceobj;
    cv::Mat image = cv::imread(ui->picpathEdit->text().toUtf8().data());
    int faceID = faceobj.face_register(image);

    if (faceID < 0) {
        QMessageBox::warning(this, "注册提示", "人脸注册失败，请检查照片");
        return;
    }

    // 检查faceID是否已存在
    QSqlQuery query;
    query.prepare("SELECT faceId FROM employee WHERE faceId = :faceId");
    query.bindValue(":faceId", faceID);
    if (query.exec() && query.next()) {
        QMessageBox::warning(this, "注册提示", "该人脸已注册，请勿重复注册");
        return;
    }

    // 把头像保存到一个固定路径下
    QString headfile = QString("./data/%1.jpg").arg(QString(ui->nameEdit->text().toUtf8().toBase64()));
    cv::imwrite(headfile.toUtf8().data(), image);

    // 2. 把个人信息存储到数据库employee
    QSqlTableModel model;
    model.setTable("employee"); // 设置表名

    // 检查数据库连接
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        QMessageBox::warning(this, "错误", "数据库未连接");
        return;
    }

    QSqlRecord record = model.record();
    // 设置数据
    record.setValue("name", ui->nameEdit->text());
    record.setValue("sex", ui->maleRb->isChecked() ? "男" : "女");
    record.setValue("birthday", ui->birthDEdit->text());
    record.setValue("address", ui->addressEdit->text());
    record.setValue("phone", ui->phoneEdit->text());
    record.setValue("faceId", faceID); // 注意字段名大小写
    record.setValue("headfile", headfile);

    // 插入记录
    bool ret = model.insertRecord(-1, record); // 在末尾插入记录
    if (ret) {
        model.submitAll(); // 提交更改
        QMessageBox::information(this, "注册提示", "注册成功");
    } else {
        qDebug() << "插入失败，错误信息：" << model.lastError().text();
        QMessageBox::warning(this, "注册提示", "注册失败：" + model.lastError().text());
    }
}

void RegisterWin::on_encamPb_clicked()
{
    if(ui->encamPb->text() == "打开摄像头"){
        if(cap.open(0)){
            ui->encamPb->setText("关闭摄像头");
            //启动定时器事件
            timerid = startTimer(100);
        }


    }else{
        killTimer(timerid);
        cap.release(); // 添加释放
        ui->encamPb->setText("打开摄像头");
    }

}

void RegisterWin::on_tkphotoPb_clicked()
{
    //保存数据
    //把头像保存到一个固定路径下
    QString headfile = QString("./data/%1.jpg").arg(QString(ui->nameEdit->text().toUtf8().toBase64()));
    ui->picpathEdit->setText(headfile);
    cv::imwrite(headfile.toUtf8().data(), image);
    killTimer(timerid);//关闭定时器事件
    ui->encamPb->setText("打开摄像头");
    //关闭摄像头
    cap.release();
}
