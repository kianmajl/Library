#include "authentication.h"
#include "ui_authentication.h"

#include <QString>

authentication::authentication(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::authentication)
{
    ui->setupUi(this);
}

authentication::~authentication()
{
    delete ui;
}

void authentication::on_pushButton_signin_clicked()
{

}
