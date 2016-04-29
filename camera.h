#ifndef Camera_H
#define Camera_H

#include "viewergl.h"
#include "ui_mainwindow.h"

//#include "opencv2/core/core.hpp"
//#include "opencv2/face.hpp"
//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/objdetect/objdetect.hpp"

#include <QThread>
#include <QMovie>
#include <QLabel>

using namespace cv;
using namespace std;

class Camera : public QObject
{

    Q_OBJECT

public:
    Camera(Ui::MainWindow *ui);
    void start();
    void stop();

private:
    Ui::MainWindow *ui;
    ViewerGl *viewer;
    QLabel *viewerMessage;

    cv::VideoCapture mCapture;

    string fn_haar;

    int im_width;
    int im_height;

    Ptr<cv::face::FaceRecognizer> model;

    CascadeClassifier haar_cascade;

    cv::Mat frame;
    Mat gray;
    Mat original;

    vector< Rect_<int> > faces;

    Mat face;
    Rect face_i;

protected:
    void timerEvent(QTimerEvent *event);

private slots:
    void update(VideoCapture);

};

class ThreadInit : public QThread
{
    Q_OBJECT

protected:

    void run()
    {
        const std::string videoStreamAddress = "http://192.168.1.106:8080/?action=stream?.mjpg";
        emit resultReady(VideoCapture(0));
    }
signals:
    void resultReady(VideoCapture);
};


#endif // Camera_H
