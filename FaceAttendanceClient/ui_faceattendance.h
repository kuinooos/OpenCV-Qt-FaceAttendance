/********************************************************************************
** Form generated from reading UI file 'faceattendance.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FACEATTENDANCE_H
#define UI_FACEATTENDANCE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FaceAttendence
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QWidget *widget_2;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *headpicLb;
    QLabel *videoLb;
    QWidget *widget_3;
    QLabel *titleLb;
    QLabel *head;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer;
    QLabel *employeeid;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_7;
    QSpacerItem *horizontalSpacer_2;
    QLabel *name;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_8;
    QSpacerItem *horizontalSpacer_3;
    QLabel *department;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_9;
    QSpacerItem *horizontalSpacer_4;
    QLabel *time;

    void setupUi(QMainWindow *FaceAttendence)
    {
        if (FaceAttendence->objectName().isEmpty())
            FaceAttendence->setObjectName(QString::fromUtf8("FaceAttendence"));
        FaceAttendence->resize(800, 480);
        centralwidget = new QWidget(FaceAttendence);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 480, 480));
        widget->setStyleSheet(QString::fromUtf8(""));
        widget_2 = new QWidget(widget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setGeometry(QRect(120, 380, 242, 59));
        widget_2->setStyleSheet(QString::fromUtf8("background-color: rgba(49, 50, 54,70);"));
        layoutWidget = new QWidget(widget_2);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(40, 10, 151, 40));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8("border-image: url(:/img/duihao.png);\n"
"background-color: rgba(49, 50, 54,70);"));

        horizontalLayout->addWidget(label);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setStyleSheet(QString::fromUtf8("font: 20pt \"\350\213\271\346\226\271 \344\270\255\347\255\211\";\n"
"color: rgb(255,255,255);\n"
"background-color: rgba(49, 50, 54,70);\n"
""));

        horizontalLayout->addWidget(label_2);

        headpicLb = new QLabel(widget);
        headpicLb->setObjectName(QString::fromUtf8("headpicLb"));
        headpicLb->setGeometry(QRect(100, 60, 266, 266));
        headpicLb->setStyleSheet(QString::fromUtf8("border-image: url(:/img/shibie.png);"));
        videoLb = new QLabel(widget);
        videoLb->setObjectName(QString::fromUtf8("videoLb"));
        videoLb->setGeometry(QRect(0, 0, 480, 480));
        videoLb->raise();
        widget_2->raise();
        headpicLb->raise();
        widget_3 = new QWidget(centralwidget);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        widget_3->setGeometry(QRect(479, -1, 321, 481));
        widget_3->setStyleSheet(QString::fromUtf8("border:1px solid #313236;\n"
"background-color: rgb(37, 40, 49,0.9);\n"
"border-radius:4px;"));
        titleLb = new QLabel(widget_3);
        titleLb->setObjectName(QString::fromUtf8("titleLb"));
        titleLb->setGeometry(QRect(0, 0, 321, 41));
        titleLb->setStyleSheet(QString::fromUtf8("font: 16pt \"\350\213\271\346\226\271 \344\270\255\347\255\211\";\n"
"color: rgb(255, 255, 255);"));
        titleLb->setAlignment(Qt::AlignCenter);
        head = new QLabel(widget_3);
        head->setObjectName(QString::fromUtf8("head"));
        head->setGeometry(QRect(90, 90, 141, 131));
        head->setStyleSheet(QString::fromUtf8("border-radius: 65px;"));
        layoutWidget1 = new QWidget(widget_3);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 240, 301, 221));
        verticalLayout = new QVBoxLayout(layoutWidget1);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_6 = new QLabel(layoutWidget1);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setMaximumSize(QSize(50, 16777215));
        label_6->setStyleSheet(QString::fromUtf8("font: 14pt \"\350\213\271\346\226\271 \344\270\255\347\255\211\";\n"
"color: rgb(125, 100, 127);\n"
"border:none;"));

        horizontalLayout_2->addWidget(label_6);

        horizontalSpacer = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        employeeid = new QLabel(layoutWidget1);
        employeeid->setObjectName(QString::fromUtf8("employeeid"));
        employeeid->setStyleSheet(QString::fromUtf8("font: 14pt \"\350\213\271\346\226\271 \344\270\255\347\255\211\";\n"
"color: white"));

        horizontalLayout_2->addWidget(employeeid);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_7 = new QLabel(layoutWidget1);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setMaximumSize(QSize(50, 16777215));
        label_7->setStyleSheet(QString::fromUtf8("font: 14pt \"\350\213\271\346\226\271 \344\270\255\347\255\211\";\n"
"color: rgb(125, 100, 127);\n"
"border:none;"));

        horizontalLayout_3->addWidget(label_7);

        horizontalSpacer_2 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        name = new QLabel(layoutWidget1);
        name->setObjectName(QString::fromUtf8("name"));
        name->setStyleSheet(QString::fromUtf8("font: 14pt \"\350\213\271\346\226\271 \344\270\255\347\255\211\";\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout_3->addWidget(name);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_8 = new QLabel(layoutWidget1);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setMaximumSize(QSize(50, 16777215));
        label_8->setStyleSheet(QString::fromUtf8("font: 14pt \"\350\213\271\346\226\271 \344\270\255\347\255\211\";\n"
"color: rgb(125, 100, 127);\n"
"border:none;"));

        horizontalLayout_4->addWidget(label_8);

        horizontalSpacer_3 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        department = new QLabel(layoutWidget1);
        department->setObjectName(QString::fromUtf8("department"));
        department->setStyleSheet(QString::fromUtf8("font: 14pt \"\350\213\271\346\226\271 \344\270\255\347\255\211\";\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout_4->addWidget(department);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_9 = new QLabel(layoutWidget1);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setMaximumSize(QSize(50, 16777215));
        label_9->setStyleSheet(QString::fromUtf8("font: 14pt \"\350\213\271\346\226\271 \344\270\255\347\255\211\";\n"
"color: rgb(125, 100, 127);\n"
"border:none;"));

        horizontalLayout_5->addWidget(label_9);

        horizontalSpacer_4 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);

        time = new QLabel(layoutWidget1);
        time->setObjectName(QString::fromUtf8("time"));
        time->setStyleSheet(QString::fromUtf8("font: 14pt \"\350\213\271\346\226\271 \344\270\255\347\255\211\";\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout_5->addWidget(time);


        verticalLayout->addLayout(horizontalLayout_5);

        FaceAttendence->setCentralWidget(centralwidget);

        retranslateUi(FaceAttendence);

        QMetaObject::connectSlotsByName(FaceAttendence);
    } // setupUi

    void retranslateUi(QMainWindow *FaceAttendence)
    {
        FaceAttendence->setWindowTitle(QCoreApplication::translate("FaceAttendence", "FaceAttendence", nullptr));
        label->setText(QString());
        label_2->setText(QCoreApplication::translate("FaceAttendence", "\350\256\244\350\257\201\346\210\220\345\212\237", nullptr));
        headpicLb->setText(QString());
        videoLb->setText(QString());
        titleLb->setText(QCoreApplication::translate("FaceAttendence", "\344\272\272\350\204\270\350\257\206\345\210\253\350\200\203\345\213\244\347\263\273\347\273\237", nullptr));
        head->setText(QString());
        label_6->setText(QCoreApplication::translate("FaceAttendence", "\345\267\245\345\217\267", nullptr));
        employeeid->setText(QString());
        label_7->setText(QCoreApplication::translate("FaceAttendence", "\345\247\223\345\220\215", nullptr));
        name->setText(QString());
        label_8->setText(QCoreApplication::translate("FaceAttendence", "\351\203\250\351\227\250", nullptr));
        department->setText(QString());
        label_9->setText(QCoreApplication::translate("FaceAttendence", "\346\227\266\351\227\264", nullptr));
        time->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class FaceAttendence: public Ui_FaceAttendence {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FACEATTENDANCE_H
