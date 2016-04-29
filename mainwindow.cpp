#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QWebView>


// Constructor
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    TV=new QWebView(this);
    TV->setGeometry(50,50,335,255);
    TV->load(QUrl("http://192.168.1.106:8080/javascript_simple.html"));

    setInterfaceEnabled(false);

    co = new Communication(this);
    timer = new QTimer();
    timer->setInterval(200);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start();
    this->foreward = false;
    this->backward = false;
    this->left = false;
    this->right = false;

}

// Destructeur
MainWindow::~MainWindow()
{
    delete ui;
}

/** BUTTON DIRECTIONS **/


// Foreward
void MainWindow::on_buttonForeward_pressed()
{
    this->foreward = true;
}
void MainWindow::on_buttonForeward_released()
{
    this->foreward = false;
}

// Right
void MainWindow::on_buttonRight_pressed()
{
    this->right = true;
}
void MainWindow::on_buttonRight_released()
{
    this->right = false;
}

// Left
void MainWindow::on_buttonLeft_pressed()
{
    this->left = true;
}

void MainWindow::on_buttonLeft_released()
{

    this->left = false;
}

// Backward
void MainWindow::on_buttonBackward_pressed()
{
    this->backward = true;
}

void MainWindow::on_buttonBackward_released()
{
    this->backward = false;
}

/** KEYBOARD **/
void MainWindow::keyPressEvent(QKeyEvent *event){
    if(co->connecte){
        if(event->key() == Qt::Key_Z){
            this->foreward = true;
        }
        else if(event->key() == Qt::Key_Q){
            this->left = true;
        }
        else if(event->key() == Qt::Key_S){
            this->backward = true;
        }
        else if(event->key() == Qt::Key_D){
            this->right = true;
        }
        else if(event->key() == Qt::Key_R){
            QUrl url("http://"+co->adresse+":8080/?action=command&dest=0&plugin=0&id=10094855&group=1&value=1");
            co->camera->get(QNetworkRequest(url));
        }
        else if(event->key() == Qt::Key_A){
            ui->vitesse->setValue(ui->vitesse->value() + 10);
        }
        else if(event->key() == Qt::Key_E){
            ui->vitesse->setValue(ui->vitesse->value() - 10);
        }
        else if(event->key() == Qt::Key_O){
                QUrl url("http://"+ co->adresse +":8080" + cameraup);
                co->camera->get(QNetworkRequest(url));
        }
        else if(event->key() == Qt::Key_L){
                QUrl url("http://"+ co->adresse +":8080" + cameradown);
                co->camera->get(QNetworkRequest(url));
        }
        else if(event->key() == Qt::Key_K){
                QUrl url("http://"+ co->adresse +":8080" + cameraleft);
                co->camera->get(QNetworkRequest(url));
        }
        else if(event->key() == Qt::Key_M){
                QUrl url("http://"+ co->adresse +":8080" + cameraright);
                co->camera->get(QNetworkRequest(url));
        }






}
}

void MainWindow::keyReleaseEvent(QKeyEvent *event){
    if(co->connecte){
        if(event->key() == Qt::Key_Z){
            this->foreward = false;
        }
        else if(event->key() == Qt::Key_Q){
            this->left = false;
        }
        else if(event->key() == Qt::Key_S){
            this->backward = false;
        }
        else if(event->key() == Qt::Key_D){
            this->right = false;
        }
    }
}

/** CAMERA **/

void MainWindow::on_CameraUp_pressed()
{
  QUrl url("http://"+ co->adresse +":8080" + cameraup);
  co->camera->get(QNetworkRequest(url));
}

void MainWindow::on_CameraDown_pressed()
{
  QUrl url("http://"+ co->adresse +":8080" + cameradown);
  co->camera->get(QNetworkRequest(url));
}

void MainWindow::on_CameraLeft_pressed()
{
  QUrl url("http://"+ co->adresse +":8080" + cameraleft);
  co->camera->get(QNetworkRequest(url));
}

void MainWindow::on_CameraRight_pressed()
{
  QUrl url("http://"+ co->adresse +":8080" + cameraright);
  co->camera->get(QNetworkRequest(url));
}




void MainWindow::on_Quitter_pressed()
{
    exit(0);
}


// Connexion
void MainWindow::on_Connexion_pressed()
{
    Connexion* connect = new Connexion(this, co);

    // Accepté
    if (connect->exec() == 1)
    {
        QMessageBox::information(this, "Connexion","Connexion réussie", QMessageBox::Ok);
        setInterfaceEnabled(true);
    }
    // Refusé
    else
    {
        QMessageBox::warning(this, "Connexion","Connexion impossible", QMessageBox::Ok);
        setInterfaceEnabled(false);
    }
}

void MainWindow::on_Deconnexion_pressed()
{
    co->Deconnexion();
    QMessageBox::information(this, "Deconnexion","Déconnexion réussie", QMessageBox::Ok);
    setInterfaceEnabled(false);
}


/** OTHER **/

// Get the user interface
Ui::MainWindow *MainWindow::getUI()
{
    return this->ui;
}

void MainWindow::update(){
    co->vitesse = ui->vitesse->value();
    if(co->connecte == true){
        ui->Batterie->setValue(co->battery);
    }
    co->foreward = this->foreward;
    co->backward = this->backward;
    co->left = this->left;
    co->right = this->right;
}

void MainWindow::setInterfaceEnabled(bool b){
    ui->buttonForeward->setEnabled(b);
    ui->buttonBackward->setEnabled(b);
    ui->buttonLeft->setEnabled(b);
    ui->buttonRight->setEnabled(b);
    ui->Batterie->setEnabled(b);
    ui->CameraUp->setEnabled(b);
    ui->CameraDown->setEnabled(b);
    ui->CameraLeft->setEnabled(b);
    ui->CameraRight->setEnabled(b);
    ui->buttonCamera->setEnabled(b);
    ui->vitesse->setEnabled(b);
}
