#ifndef QFACEOBJECT_H
#define QFACEOBJECT_H

#include <QObject>
#include <seeta/FaceEngine.h>
#include <opencv2/opencv.hpp>
#include <QtDebug>

using namespace seeta;
using namespace cv;

class QFaceObject : public QObject
{
    Q_OBJECT
public:
    explicit QFaceObject(QObject *parent = nullptr);
    ~QFaceObject();

public slots:
    qint64 face_register(cv::Mat &faceImage);
    qint64 face_query(cv::Mat &faceImage);
signals:
    void send_faceid(int64_t faceid);
private:
    static seeta::FaceEngine *fengineptr;
    static void initializeDatabase();
};

#endif // QFACEOBJECT_H
