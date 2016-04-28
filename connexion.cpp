#include "connexion.h"

Connexion::Connexion(QWidget *parent, Communication *co) :
    QDialog(parent),
    ui(new Ui::Connexion)
{
    ui->setupUi(this);
    this->co = co;
    this->parent = parent;
}

Connexion::~Connexion()
{
    delete ui;
}

void Connexion::on_buttonBox_accepted()
{
    QString address = ui->lineEdit_address->text();
    quint16 port = quint16(ui->lineEdit_port->text().toInt());


    if(co->Connexion(address, port))
    {
        this->accept();
    }
    else
    {
        this->reject();
    }
}
