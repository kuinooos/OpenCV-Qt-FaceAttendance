# FaceAttendance - 人脸识别考勤系统

## 项目简介
基于Qt和OpenCV的跨平台人脸识别考勤系统，包含客户端和服务端两部分：
- **客户端**：实现人脸图像采集、用户界面交互
- **服务端**：提供人脸识别引擎、数据库存储、网络通信服务

## 技术栈
| 模块       | 技术/工具                  | 说明                     |
|------------|---------------------------|--------------------------|
| **客户端** | Qt 5.14.2                 | 图形界面开发             |
|            | OpenCV 4.5.2               | 视频流处理与人脸检测     |
|            | QTcpSocket                | TCP协议网络通信          |
| **服务端** | Qt 5.14.2                 | 网络服务与多线程处理     |
|            | SeetaFace 6               | 人脸识别核心算法         |
|            | SQLite 3.36               | 本地数据库存储           |
| **通用**   | JSON                      | 数据传输格式             |
|            | TCP/IP                    | 网络通信协议             |

## 项目结构
```bash
FaceAttendance/
├── client/                # 客户端代码
│   ├── FaceAttendence.pro  # Qt项目配置文件
│   ├── faceattendance.ui   # 界面设计文件
│   ├── faceattendance.h    # 主窗口类定义
│   ├── faceattendance.cpp  # 主窗口功能实现
│   ├── main.cpp            # 程序入口
│   └── img/                # 界面资源
├── server/                # 服务端代码
│   ├── attendancewin.h     # 服务窗口类定义
│   ├── attendancewin.cpp   # 服务窗口功能实现
│   ├── main.cpp            # 服务端入口
│   └── server.db           # SQLite数据库文件
├── LICENSE                # 开源协议
└── README.md              # 项目说明文档

