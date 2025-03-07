#include "selectwin.h"
#include "ui_selectwin.h"
#include <QSqlTableModel>
#include <QDebug>
#include <QSqlError>

SelectWin::SelectWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectWin)
{
    ui->setupUi(this);

    // 连接数据库并检查是否成功
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("server.db");

    if (!db.open()) {
        qDebug() << "数据库连接失败：" << db.lastError().text();
    } else {
        qDebug() << "数据库连接成功！";
    }
}

SelectWin::~SelectWin()
{
    delete ui;
}

void SelectWin::on_selectBt_clicked()
{
    QSqlTableModel *sqlmodel = new QSqlTableModel(nullptr,db);
    if(ui->empRd->isChecked()){
        sqlmodel->setTable("employee");
        sqlmodel->select();
    }else{
        sqlmodel->setTable("attendance");
        sqlmodel->select();
    }

    // 设置模型到视图
    ui->tableView->setModel(sqlmodel);
}

