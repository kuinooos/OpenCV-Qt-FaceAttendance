#include "qfaceobject.h"
#include <QFile>
#include <QDebug>

seeta::FaceEngine* QFaceObject::fengineptr = nullptr;

QFaceObject::QFaceObject(QObject *parent) : QObject(parent)
{
    if (fengineptr == nullptr) {
        // 初始化模型路径
        seeta::ModelSetting FDmodel("D:\\FaceRecognitionAttendanceSystem\\SeetaFace\\bin\\model\\fd_2_00.dat");
        seeta::ModelSetting PDmodel("D:\\FaceRecognitionAttendanceSystem\\SeetaFace\\bin\\model\\pd_2_00_pts5.dat");
        seeta::ModelSetting FRmodel("D:\\FaceRecognitionAttendanceSystem\\SeetaFace\\bin\\model\\fr_2_10.dat");
        fengineptr = new seeta::FaceEngine(FDmodel, PDmodel, FRmodel);
        initializeDatabase(); // 仅在首次初始化时调用
    }
}

QFaceObject::~QFaceObject()
{
    // 注意：静态成员需在程序退出时手动释放
}

void QFaceObject::initializeDatabase()
{
    static bool initialized = false;
    if (!initialized) {
        if (QFile::exists("./face.db")) {
            if (!fengineptr->Load("./face.db")) {
                qDebug() << "人脸数据库加载失败，可能是文件损坏。";
            } else {
                qDebug() << "人脸数据库加载成功。";
            }
        } else {
            if (!fengineptr->Save("./face.db")) {
                qDebug() << "人脸数据库初始化失败。";
            } else {
                qDebug() << "人脸数据库已初始化。";
            }
        }
        initialized = true;
    }
}

int64_t QFaceObject::face_register(cv::Mat &faceImage)
{
    if (faceImage.empty()) {
        qDebug() << "输入图像为空，无法注册。";
        return -1;
    }

    SeetaImageData simage;
    simage.data = faceImage.data;
    simage.width = faceImage.cols;
    simage.height = faceImage.rows;
    simage.channels = faceImage.channels();

    std::vector<SeetaFaceInfo> faces = fengineptr->DetectFaces(simage);
    if (faces.empty()) {
        qDebug() << "未检测到人脸，注册失败。";
        return -1;
    }

    float sml=0;
    int64_t existingFaceid = fengineptr->Query(simage,&sml);
    if(existingFaceid>=0&&sml>0.7){
        qDebug() << "人脸已存在，返回已注册的faceId：" <<existingFaceid;
        return existingFaceid;
    }

    int64_t faceid = fengineptr->Register(simage);
    if (faceid < 0) {
        qDebug() << "人脸注册失败。";
        return -1;
    }
    qDebug() << "注册人脸 ID：" << faceid;

    int face_count = fengineptr->Count();
    qDebug() << "数据库当前人脸数：" << face_count;

    if (!fengineptr->Save("./face.db")) {
        qDebug() << "人脸数据库保存失败。";
        return -1;
    }

    return faceid;
}

int64_t QFaceObject::face_query(cv::Mat &faceImage)
{
    SeetaImageData simage;
    simage.data = faceImage.data;
    simage.width = faceImage.cols;
    simage.height = faceImage.rows;
    simage.channels = faceImage.channels();
    float similarity = 0;
    int64_t faceid = fengineptr->Query(simage, &similarity);
    qDebug() << "查询结果 ID：" << faceid << "相似度：" << similarity;
    emit send_faceid(similarity > 0.4 ? faceid : -1);
    return faceid;
}
