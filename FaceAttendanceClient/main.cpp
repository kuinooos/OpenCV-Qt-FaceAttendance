#include "faceattendance.h"

#include <QApplication>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FaceAttendance w;
    w.show();
    return a.exec();
}
