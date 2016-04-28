#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "communication.h"


#include <QtWidgets/QWidget>
#include "connexion.h"

#include <unistd.h>
#include <QtWidgets>
#include <qvideowidget.h>
#include <qvideosurfaceformat.h>
#include <QKeyEvent>

#include <QMainWindow>
#include <QTimer>

#include <QWebView>
#include<QUrl>

#define cameraup "/?action=command&dest=0&plugin=0&id=10094853&group=1&value=-200"
#define cameradown "/?action=command&dest=0&plugin=0&id=10094853&group=1&value=200"
#define cameraleft "/?action=command&dest=0&plugin=0&id=10094852&group=1&value=200"
#define cameraright "/?action=command&dest=0&plugin=0&id=10094852&group=1&value=-200"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void modifyLabel(QString, QString);
    Ui::MainWindow * getUI();
    bool foreward;
    bool backward;
    bool left;
    bool right;
    QTimer *timer;
    Communication* co;
    void keyReleaseEvent(QKeyEvent *event);
    void keyPressEvent(QKeyEvent *event);

private slots:

    void on_buttonRight_pressed();
    void on_buttonRight_released();

    void on_buttonLeft_pressed();
    void on_buttonLeft_released();

    void on_buttonForeward_pressed();
    void on_buttonForeward_released();

    void on_buttonBackward_pressed();
    void on_buttonBackward_released();

    void on_CameraUp_pressed();
    void on_CameraDown_pressed();
    void on_CameraLeft_pressed();
    void on_CameraRight_pressed();

    void on_Quitter_pressed();
    void on_Connexion_pressed();
    void on_Deconnexion_pressed();
    void update();



private:
    QWebView* TV;
Ui::MainWindow *ui;
    QProgressBar *battery;

    void setInterfaceEnabled(bool b);


};




#endif // MAINWINDOW_H
