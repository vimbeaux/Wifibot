#ifndef CONNEXION_H
#define CONNEXION_H

#include "communication.h"
#include "mainwindow.h"
#include "ui_connexion.h"
#include "ui_mainwindow.h"

#include <QDialog>


namespace Ui {
class Connexion;
}

class Connexion : public QDialog
{
    Q_OBJECT

public:
    explicit Connexion(QWidget *parent, Communication *co);
    ~Connexion();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Connexion *ui;
    Communication* co;
    QWidget* parent;
};

#endif // CONNEXION_H
