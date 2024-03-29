#include "inbox.h"
#include "ui_inbox.h"

inbox::inbox(Ui::MainWindow *ui_admindash, const QString &user, const bool &isAdmin, QWidget *dash, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::inbox)
{
    this->change = false;
    this->ui_admindash = ui_admindash;
    this->isAdmin = isAdmin;
    this->dash = dash;
    this->user = user;
    ui->setupUi(this);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->messages_data = Message::loadMessages(); // code - sender - reciver - subject - text - isRead
    this->LoadData();
}

inbox::inbox(Ui::MainWindow_user *ui_userdash, const QString &user, const bool &isAdmin, QWidget *dash, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::inbox)
{
    this->change = false;
    this->ui_userdash = ui_userdash;
    this->isAdmin = isAdmin;
    this->dash = dash;
    this->user = user;
    ui->setupUi(this);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->messages_data = Message::loadMessages(); // code - sender - reciver - subject - text - isRead
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
    QMapIterator<QString, QStringList> i(messages_data);
    i.toBack();
    while (i.hasPrevious())
    {
        i.previous();
        if (i.value().at(1) == user)
        {
            ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            QString date = QDateTime::fromString(i.key(), "yyyyMMddhhmmsszzz").toString("dd MMMM yyyy hh:mm:ss.zzz");
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
        QString code_msg = QDateTime::fromString(tmp->text(), "dd MMMM yyyy hh:mm:ss.zzz").toString("yyyyMMddhhmmsszzz");
        ui->plainTextEdit->show();
        ui->plainTextEdit->setPlainText(messages_data.value(code_msg).at(3));
    }
}

void inbox::on_pushButton_delete_clicked()
{
    if (!ui->tableWidget->selectedItems().size())
    {
        QMessageBox::critical(nullptr, "No Item Selected", "Please select an item to delete");
        return;
    }
    QString code = QDateTime::fromString(ui->tableWidget->selectedItems().at(0)->text(), "dd MMMM yyyy hh:mm:ss.zzz").toString("yyyyMMddhhmmsszzz");
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
        QMessageBox::critical(nullptr, "No Item Selected", "Please select an item to mark as read");
        return;
    }
    QString code = QDateTime::fromString(ui->tableWidget->selectedItems().at(0)->text(), "dd MMMM yyyy hh:mm:ss.zzz").toString("yyyyMMddhhmmsszzz");
    messages_data[code][4] = QString::number(true);
    saveChanges();
    LoadData();
    this->change = true;
}

void inbox::on_pushButton_reply_clicked()
{
    if (!ui->tableWidget->selectedItems().size())
    {
        QMessageBox::critical(nullptr, "No Item Selected", "Please select an item to reply");
        return;
    }
    QString code = QDateTime::fromString(ui->tableWidget->selectedItems().at(0)->text(), "dd MMMM yyyy hh:mm:ss.zzz").toString("yyyyMMddhhmmsszzz");
    if (ui->tableWidget->selectedItems().at(1)->text() != "SYSTEM")
    {
        Compose * cmp = new Compose(this, this->user, messages_data[code].at(0), "Re: " + messages_data[code].at(2));
        this->hide();
        cmp->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
        cmp->show();
    }
    else
        QMessageBox::warning(nullptr, "SYSTEM", "You can not send message to SYSTEM!");
    on_pushButton_asread_clicked();
}

void inbox::on_pushButton_forward_clicked()
{
    if (!ui->tableWidget->selectedItems().size())
    {
        QMessageBox::critical(nullptr, "No Item Selected", "Please select an item to forward");
        return;
    }
    QString code = QDateTime::fromString(ui->tableWidget->selectedItems().at(0)->text(), "dd MMMM yyyy hh:mm:ss.zzz").toString("yyyyMMddhhmmsszzz");
    Compose * cmp = new Compose(this, this->user, "", "Fw: " + messages_data[code].at(2), messages_data[code].at(3));
    this->hide();
    cmp->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    cmp->show();
    on_pushButton_asread_clicked();
}
