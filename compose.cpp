#include "compose.h"
#include "ui_compose.h"

Compose::Compose(QWidget *dash, QString sender, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Compose)
{
    this->dash = dash;
    this->sender = sender;
    ui->setupUi(this);
    ui->lineEdit_sender->setText(sender);
}

Compose::~Compose()
{
    delete ui;
}

void Compose::on_pushButton_backtodash_clicked()
{
    this->close();
    dash->show();
    delete this;
}
