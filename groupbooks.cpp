#include "groupbooks.h"
#include "ui_groupbooks.h"

#define GROUP_FILE "groupdb.txt"

groupBooks::groupBooks(QWidget *admin_dash, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::groupBooks)
{
    this->admin_dash = admin_dash;
    ui->setupUi(this);
    int num_loaded_data = this->LoadData();
    ui->label->setText("Group Books | " + QString::number(num_loaded_data) + " Records Loaded");
}

void groupBooks::mousePressEvent(QMouseEvent *event)
{
    oldPos = event->globalPosition();
}

void groupBooks::mouseMoveEvent(QMouseEvent *event)
{
    const QPointF delta = event->globalPosition() - oldPos;
    move(x()+delta.x(), y()+delta.y());
    oldPos = event->globalPosition();
}

int groupBooks::LoadData()
{
}

groupBooks::~groupBooks()
{
    delete ui;
}

void groupBooks::on_lineEdit_textChanged(const QString &arg1)
{
    QList<QListWidgetItem *> qlwi = ui->listWidget->findItems(arg1, Qt::MatchExactly);
    for (const auto &i : qlwi)
        ui->listWidget->setCurrentItem(i);
}

void groupBooks::on_listWidget_currentTextChanged(const QString &currentText)
{
    ui->lineEdit->setText(currentText);
}

void groupBooks::on_pushButton_backtodash_clicked()
{
    this->close();
    admin_dash->show();
}
