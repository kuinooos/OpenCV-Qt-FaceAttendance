#ifndef REGISTERWIN_H
#define REGISTERWIN_H

#include <QWidget>
#include <QFileDialog>
#include <QDate>
#include "qfaceobject.h"
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QMessageBox>
#include <QSqlDatabase>

namespace Ui {
class RegisterWin;
}

class RegisterWin : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterWin(QWidget *parent = nullptr);
    ~RegisterWin();

    void timerEvent(QTimerEvent* event) override;
private slots:
    void on_resetPb_clicked();

    void on_addheadPb_clicked();

    void on_registerPb_clicked();

    void on_encamPb_clicked();

    void on_tkphotoPb_clicked();

private:
    Ui::RegisterWin *ui;
    int timerid;
    cv::VideoCapture cap;
    cv::Mat image;
};

#endif // REGISTERWIN_H
