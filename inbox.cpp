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

int inbox::LoadData()
{
    ui->tableWidget->setRowCount(0);
    int j = 0;

    // Add to table
    for (auto i = messages_data.begin(); i != messages_data.end(); ++i)
    {
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        QString date = QDateTime::fromString(i.key(), "yyMMddhhmmss").toString("dd MMMM yy hh:mm:ss");
        ui->tableWidget->setItem(j, 0, new QTableWidgetItem(date));
        ui->tableWidget->setItem(j, 1, new QTableWidgetItem(i.value()[0]));
        ui->tableWidget->setItem(j, 2, new QTableWidgetItem((i.value()[2])));
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
