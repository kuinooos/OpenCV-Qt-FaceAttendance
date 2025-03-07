#ifndef ATTENDANCEWIN_H
#define ATTENDANCEWIN_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <opencv2/opencv.hpp>
#include <qfaceobject.h>
#include "registerwin.h"

QT_BEGIN_NAMESPACE
namespace Ui { class AttendanceWin; }
QT_END_NAMESPACE

class AttendanceWin : public QMainWindow
{
    Q_OBJECT

public:
    AttendanceWin(QWidget *parent = nullptr);
    ~AttendanceWin();

signals:
    void query(cv::Mat& image);

private slots:
    void read_data();

    void recv_faceid(int64_t faceId);
private:
    Ui::AttendanceWin *ui;

    QTcpServer mserver;
    QTcpSocket *msocket;

    quint64 bsize;

    QFaceObject fobject;
};
#endif // ATTENDANCEWIN_H
