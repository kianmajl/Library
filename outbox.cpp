#include "outbox.h"
#include "ui_outbox.h"

outbox::outbox(QWidget *dash, QString user, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::outbox)
{
    this->dash = dash;
    this->user = user;
    ui->setupUi(this);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    loadData();
}

void outbox::mousePressEvent(QMouseEvent *event)
{
    oldPos = event->globalPosition();
}

void outbox::mouseMoveEvent(QMouseEvent *event)
{
    const QPointF delta = event->globalPosition() - oldPos;
    move(x()+delta.x(), y()+delta.y());
    oldPos = event->globalPosition();
}

int outbox::loadData()
{
    this->messagedb = Message::loadMessages(); // code - sender - reciver - subject - text - isRead
    ui->tableWidget->setRowCount(0);
    ui->plainTextEdit->hide();
    int j = 0;

    // Add to table
    QMapIterator<QString, QStringList> i(messagedb);
    i.toBack();
    while (i.hasPrevious())
    {
        i.previous();
        if (i.value().at(0) == user)
        {
            ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            QString date = QDateTime::fromString(i.key(), "yyyyMMddhhmmsszzz").toString("dd MMMM yyyy hh:mm:ss.zzz");
            ui->tableWidget->setItem(j, 0, new QTableWidgetItem(date));
            ui->tableWidget->setItem(j, 1, new QTableWidgetItem(i.value().at(1)));
            ui->tableWidget->setItem(j, 2, new QTableWidgetItem(i.value().at(2)));
            ui->tableWidget->setItem(j, 3, new QTableWidgetItem((i.value().at(4).toInt()) ? "Yes" : "No"));
            ++j;
        }
    }

    ui->label->setText("Outbox | " + QString::number(j) +" Records Loaded");
    return j;

}

outbox::~outbox()
{
    delete ui;
}

void outbox::on_pushButton_clicked()
{
    this->loadData();
}

void outbox::on_tableWidget_currentCellChanged(int currentRow)
{
    QTableWidgetItem *tmp = ui->tableWidget->item(currentRow, 0);
    if (tmp) // if item exists !
    {
        QString code_msg = QDateTime::fromString(tmp->text(), "dd MMMM yyyy hh:mm:ss.zzz").toString("yyyyMMddhhmmsszzz");
        ui->plainTextEdit->show();
        ui->plainTextEdit->setPlainText(messagedb.value(code_msg).at(3));
    }
}

void outbox::on_pushButton_backtodash_clicked()
{
    this->hide();
    dash->show();
}
