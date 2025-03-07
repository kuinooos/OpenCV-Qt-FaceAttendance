#include "attendancewin.h"

#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "registerwin.h"
#include "selectwin.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<cv::Mat>("cv::Mat&");
    qRegisterMetaType<int64_t>("int64_t");

    //连接数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    //数据库名称
    QDir dir;
    if(!dir.exists("./server.db")){
        if(dir.mkdir("./server.db")){
            qDebug() << "server数据库创建成功";
        }else{
            qDebug() << "server数据库创建失败";
        }
    }
    db.setDatabaseName("server.db");
    if(!db.open()){
        qDebug() << db.lastError().text();
        return -1;
    }

    //创建员工表格
    QString createsql = "create table if not exists employee(employeeId integer primary key autoincrement,"
                        "name varchar(256),sex varchar(32),birthday text,address text,phone text,faceId integer unique,headfile text)";
    QSqlQuery query(db);
    if(!query.exec(createsql)){
        qDebug() << query.lastError().text();
        return -1;
    }
    //创建出勤表
    QString createsql1 = "create table if not exists attendance(attendanceId integer primary key autoincrement,"
                        "employeeId integer,attendanceTime TimeStamp NOT NULL DEFAULT CURRENT_TIMESTAMP)";
    if(!query.exec(createsql1)){
        qDebug() << query.lastError().text();
        return -1;
    }

    AttendanceWin w;
    w.show();

    return a.exec();
}
