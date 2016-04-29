#include "camera.h"

Camera::Camera(Ui::MainWindow *ui)
{
    this->ui = ui;
    viewer = new ViewerGl();
    viewerMessage = new QLabel();

    fn_haar = "/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_default.xml";
    haar_cascade.load(fn_haar);

    qRegisterMetaType<VideoCapture>("VideoCapture");
}

// Start the camera
void Camera::start()
{
    if (!mCapture.isOpened())
    {
        // Loading step
        QMovie *movie = new QMovie(":/loading.gif");
        viewerMessage->setMovie(movie);
        movie->start();
        ui->dockWidgetCamera->setWidget(viewerMessage);

        ui->dockWidgetCamera->setVisible(true);

        ThreadInit *t = new ThreadInit();
        connect(t, SIGNAL(resultReady(VideoCapture)), this, SLOT(update(VideoCapture)));
        t->start();
    }
    else
    {
        ui->statusBar->showMessage(tr("/!\\ Camera is not available"));
    }
}

// Stop the camera
void Camera::stop()
{
    if (mCapture.isOpened())
    {
        ui->dockWidgetCamera->setVisible(false);
        mCapture.release();

    }
}

// Signal update
void Camera::update(VideoCapture c)
{
    if(c.isOpened())
    {
        mCapture = c;
        ui->dockWidgetCamera->setWidget(viewer);
        startTimer(0);
    }
    else
    {
        ui->statusBar->showMessage(tr("/!\\ Stream not found"));

        QMovie *movie = new QMovie(":/error.gif");
        viewerMessage->setMovie(movie);
        movie->start();
        ui->dockWidgetCamera->setWidget(viewerMessage);

        ui->dockWidgetCamera->setWidget(viewerMessage);
    }
}

// Loop image processing face detection
void Camera::timerEvent(QTimerEvent *event)
{
    mCapture >> frame;

    if(frame.empty())
        return;

    cvtColor(frame, gray, CV_BGR2GRAY);

    // Find the faces in the frame
    haar_cascade.detectMultiScale(gray, faces, 1.2, 2, 0|CV_HAAR_SCALE_IMAGE,Size(100, 100));

    for(unsigned int i = 0; i < faces.size(); i++) {
        // Process face by face:
        face_i = faces[i];
        // Crop the face from the image. So simple with OpenCV C++:
        face = gray(face_i);
        // Draw a green rectangle around the detected face:
        rectangle(frame, face_i, CV_RGB(0, 255,0), 2);
    }

    // Show the image
    viewer->showImage( frame );
}
