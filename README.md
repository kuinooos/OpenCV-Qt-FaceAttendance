# FaceAttendance - 人脸识别考勤系统

## 项目简介
FaceAttendance 是一个基于 Qt 和 OpenCV 的跨平台人脸识别考勤系统，包含客户端和服务端两部分：
- **客户端**：实现人脸图像采集、用户界面交互。
- **服务端**：提供人脸识别引擎、数据库存储、网络通信服务。

## 技术栈
| 模块       | 技术/工具                  | 说明                     |
|------------|---------------------------|--------------------------|
| **客户端** | Qt 5.14.2                 | 图形界面开发             |
|            | OpenCV 4.x                | 视频流处理与人脸检测     |
|            | QTcpSocket                | TCP 协议网络通信         |
| **服务端** | Qt 5.14.2                 | 网络服务与多线程处理     |
|            | SeetaFace 2.x             | 人脸识别核心算法         |
|            | SQLite 3.36               | 本地数据库存储           |
| **通用**   | JSON                      | 数据传输格式             |
|            | TCP/IP                    | 网络通信协议             |

## 项目结构
```bash
FaceAttendance/
├── client/                # 客户端代码
│   ├── FaceAttendance.pro  # Qt 项目配置文件
│   ├── faceattendance.ui   # 界面设计文件
│   ├── faceattendance.h    # 主窗口类定义
│   ├── faceattendance.cpp  # 主窗口功能实现
│   ├── main.cpp            # 程序入口
│   └── img/                # 界面资源
├── server/                # 服务端代码
│   ├── attendancewin.h     # 服务窗口类定义
│   ├── attendancewin.cpp   # 服务窗口功能实现
│   ├── main.cpp            # 服务端入口
│   └── server.db           # SQLite 数据库文件
├── LICENSE                # 开源协议
└── README.md              # 项目说明文档
```
## 核心功能
### 客户端功能
- **实时视频流显示**
  - 通过 OpenCV 捕获摄像头画面。
  - 支持画面缩放与自适应显示。
- **人脸数据采集**
  - 手动触发图像采集。
  - 自动检测画面中的人脸区域。
- **网络通信**
  - 与服务端建立 TCP 连接。
  - 发送 JPEG 格式人脸图像数据。
  - 接收 JSON 格式识别结果。

### 服务端功能
- **网络服务**
  - 监听 9999 端口等待客户端连接。
  - 支持多客户端并发访问。
- **人脸识别**
  - 使用 SeetaFace 引擎实现 1:1 比对。
  - 支持百万级人脸库快速检索。
- **数据存储**
  - 采用 SQLite 存储考勤信息。
  ```sql
  CREATE TABLE employee (
      faceId INTEGER PRIMARY KEY,
      employeeId VARCHAR(20),
      name VARCHAR(50),
      department VARCHAR(50)
  );
  
  CREATE TABLE attendance (
      id INTEGER PRIMARY KEY AUTOINCREMENT,
      employeeId VARCHAR(20),
      time DATETIME DEFAULT CURRENT_TIMESTAMP
  );
  ```

## 使用说明
### 环境配置
#### 客户端依赖
- OpenCV 4.1.2
- SeetaFace 6

### 操作流程
#### **员工注册**
1. 通过管理后台录入员工信息并上传人脸照片。
2. 系统自动生成唯一 `faceId` 存储到数据库。

#### **日常考勤**
1. 打开客户端选择摄像头。
2. 系统自动检测人脸并发送到服务端。
3. 服务端返回考勤结果并更新数据库。

## 开源协议
本项目采用 **MIT License**，允许自由使用、修改和分发，但需保留版权声明。

## 贡献指南
- 提交代码前请运行代码格式化工具（如 `clang-format`）。
- 新功能需添加单元测试。
- 重大变更需提前提交 Issue 讨论。

## 联系方式
- **项目主页**：[https://github.com/kuinooos/OpenCV-Qt-FaceAttendance](https://github.com/kuinooos/OpenCV-Qt-FaceAttendance)
- **问题反馈**：提交 Issue。
- **作者邮箱**：1832578485@qq.com。
```

