#include "inbox.h"
#include "ui_inbox.h"

inbox::inbox(Ui::MainWindow *ui_admindash, QString user, bool isAdmin, QWidget *dash, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::inbox)
{
    this->change = false;
    this->ui_admindash = ui_admindash;
    this->isAdmin = isAdmin;
    this->dash = dash;
    this->user = user;
    this->messages_data = Message::loadMessages(); // code - sender - reciver - subject - text - isRead
    ui->setupUi(this);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->LoadData();
}

inbox::inbox(Ui::MainWindow_user *ui_userdash, QString user, bool isAdmin, QWidget *dash, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::inbox)
{
    this->change = false;
    this->ui_userdash = ui_userdash;
    this->isAdmin = isAdmin;
    this->dash = dash;
    this->user = user;
    this->messages_data = Message::loadMessages(); // code - sender - reciver - subject - text - isRead
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
    ui->plainTextEdit->hide();
    int j = 0;

    // Add to table
    for (auto i = messages_data.constBegin(); i != messages_data.constEnd(); ++i)
    {
        if (i.value().at(1) == user)
        {
            ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            QString date = QDateTime::fromString(i.key(), "yyyyMMddhhmmss").toString("dd MMMM yyyy hh:mm:ss");
            ui->tableWidget->setItem(j, 0, new QTableWidgetItem(date));
            ui->tableWidget->setItem(j, 1, new QTableWidgetItem(i.value().at(0)));
            ui->tableWidget->setItem(j, 2, new QTableWidgetItem(i.value().at(2)));
            ui->tableWidget->setItem(j, 3, new QTableWidgetItem((i.value().at(4).toInt()) ? "Yes" : "No"));
            ++j;
        }
    }

    ui->label->setText("Inbox | " + QString::number(j) +" Records Loaded");
    return j;
}

bool inbox::saveChanges()
{
    return Message::saveChanges(messages_data);
}

inbox::~inbox()
{
    delete ui;
}

void inbox::on_pushButton_backtodash_clicked()
{
    this->hide();
    if (change)
    {
        int unreadmsg = Message::numUnreadMessages(user);

        if (isAdmin)
        {
            if (unreadmsg)
                ui_admindash->statusbar->showMessage("You Have " + QString::number(unreadmsg) + " Unread Messages");
            else
                ui_admindash->statusbar->clearMessage();
        }
        else
        {
            if (unreadmsg)
                ui_userdash->statusbar->showMessage("You Have " + QString::number(unreadmsg) + " Unread Messages");
            else
                ui_userdash->statusbar->clearMessage();
        }

        this->change = false;
    }
    dash->show();
}

void inbox::on_tableWidget_currentCellChanged(int currentRow)
{
    QTableWidgetItem *tmp = ui->tableWidget->item(currentRow, 0);
    if (tmp) // if item exists !
    {
        QString code_msg = QDateTime::fromString(tmp->text(), "dd MMMM yyyy hh:mm:ss").toString("yyyyMMddhhmmss");
        ui->plainTextEdit->show();
        ui->plainTextEdit->setPlainText(messages_data.value(code_msg).at(3));
    }
}

void inbox::on_pushButton_delete_clicked()
{
    if (!ui->tableWidget->selectedItems().size())
    {
        QMessageBox::critical(nullptr, "No Item Selected", "Please Select an Item to delete");
        return;
    }
    QString code = QDateTime::fromString(ui->tableWidget->selectedItems().at(0)->text(), "dd MMMM yyyy hh:mm:ss").toString("yyyyMMddhhmmss");
    int ret = QMessageBox::warning(nullptr, "Confirm Delete Message", "Are you sure you want to delete this message?", QMessageBox::Yes | QMessageBox::No);
    if (ret == QMessageBox::Yes)
        messages_data.remove(code);
    saveChanges();
    LoadData();
    this->change = true;
}

void inbox::on_pushButton_asread_clicked()
{
    if (!ui->tableWidget->selectedItems().size())
    {
        QMessageBox::critical(nullptr, "No Item Selected", "Please Select an Item to mark as read");
        return;
    }
    QString code = QDateTime::fromString(ui->tableWidget->selectedItems().at(0)->text(), "dd MMMM yyyy hh:mm:ss").toString("yyyyMMddhhmmss");
    messages_data[code][4] = QString::number(true);
    saveChanges();
    LoadData();
    this->change = true;
}

void inbox::on_pushButton_reply_clicked()
{
    if (!ui->tableWidget->selectedItems().size())
    {
        QMessageBox::critical(nullptr, "No Item Selected", "Please Select an Item to reply");
        return;
    }
    on_pushButton_asread_clicked();
    QString code = QDateTime::fromString(ui->tableWidget->selectedItems().at(0)->text(), "dd MMMM yyyy hh:mm:ss").toString("yyyyMMddhhmmss");
    Compose * cmp = new Compose(this, this->user, messages_data[code].at(0), "Re: " + messages_data[code].at(2));
    this->hide();
    cmp->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    cmp->show();
}

void inbox::on_pushButton_forward_clicked()
{
    if (!ui->tableWidget->selectedItems().size())
    {
        QMessageBox::critical(nullptr, "No Item Selected", "Please Select an Item to forward");
        return;
    }
    on_pushButton_asread_clicked();
    QString code = QDateTime::fromString(ui->tableWidget->selectedItems().at(0)->text(), "dd MMMM yyyy hh:mm:ss").toString("yyyyMMddhhmmss");
    Compose * cmp = new Compose(this, this->user, "", "Fw: " + messages_data[code].at(2), messages_data[code].at(3));
    this->hide();
    cmp->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    cmp->show();
}
