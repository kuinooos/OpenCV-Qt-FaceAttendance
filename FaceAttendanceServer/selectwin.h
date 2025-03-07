#ifndef SELECTWIN_H
#define SELECTWIN_H

#include <QWidget>
#include <QtSql/QSqlDatabase>
#include <QStandardItemModel>

namespace Ui {
class SelectWin;
}

class SelectWin : public QWidget
{
    Q_OBJECT

public:
    explicit SelectWin(QWidget *parent = nullptr);
    ~SelectWin();

private slots:
    void on_selectBt_clicked();

private:
    Ui::SelectWin *ui;

    QSqlDatabase db;
};

#endif // SELECTWIN_H
