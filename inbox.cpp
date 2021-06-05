#include "inbox.h"
#include "ui_inbox.h"

inbox::inbox(QString user, QWidget *dash, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::inbox)
{
    this->dash = dash;
    this->messages_data = Message::loadMessages(user); // code - sender - reciver - subject - text - isRead
    ui->setupUi(this);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->LoadData();
}

void inbox::mousePressEvent(QMouseEvent *event)
{
    oldPos = event->globalPosition();
}

void inbox::mouseMoveEvent(QMouseEvent *event)
{
    const QPointF delta = event->globalPosition() - oldPos;
    move(x()+delta.x(), y()+delta.y());
    oldPos = event->globalPosition();
}

int inbox::LoadData()
{
    ui->tableWidget->setRowCount(0);
    int j = 0;

    // Add to table
    for (auto i = messages_data.begin(); i != messages_data.end(); ++i)
    {
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        QString date = QDateTime::fromString(i.key(), "yyyyMMddhhmmss").toString("dd MMMM yyyy hh:mm:ss");
        ui->tableWidget->setItem(j, 0, new QTableWidgetItem(date));
        ui->tableWidget->setItem(j, 1, new QTableWidgetItem(i.value()[0]));
        ui->tableWidget->setItem(j, 2, new QTableWidgetItem(i.value()[2]));
        ui->tableWidget->setItem(j, 3, new QTableWidgetItem((i.value()[4].toInt()) ? "Yes" : "No"));
        ++j;
    }

    ui->label->setText("Inbox | " + QString::number(j) +" Records Loaded");
    return j;
}

inbox::~inbox()
{
    delete ui;
}

void inbox::on_pushButton_backtodash_clicked()
{
    this->close();
    dash->show();
}

void inbox::on_tableWidget_currentCellChanged(int currentRow)
{
    QTableWidgetItem *tmp = ui->tableWidget->item(currentRow, 0);
    if (tmp) // if item exists !
    {
        QString code_msg = QDateTime::fromString(tmp->text(), "dd MMMM yyyy hh:mm:ss").toString("yyyyMMddhhmmss");
        ui->plainTextEdit->setPlainText(messages_data.value(code_msg)[3]);
    }
}
