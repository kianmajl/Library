#include "compose.h"
#include "ui_compose.h"

Compose::Compose(QWidget *dash, QString sender, QString reciver, QString subject, QString txt, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Compose)
{
    this->dash = dash;
    this->sender = sender;
    this->users = User::LoadUsers();
    ui->setupUi(this);
    ui->lineEdit_sender->setText(sender);
    ui->lineEdit_reciver->setText(reciver);
    ui->lineEdit_subject->setText(subject);
    ui->plainTextEdit->setPlainText(txt);
    QCompleter *completer = new QCompleter(users.keys(), this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setCompletionMode(QCompleter::InlineCompletion);
    ui->lineEdit_reciver->setCompleter(completer);
}

void Compose::mousePressEvent(QMouseEvent *event)
{
    oldPos = event->globalPosition();
}

void Compose::mouseMoveEvent(QMouseEvent *event)
{
    const QPointF delta = event->globalPosition() - oldPos;
    move(x()+delta.x(), y()+delta.y());
    oldPos = event->globalPosition();
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

void Compose::on_pushButton_clicked()
{
    if (!ui->lineEdit_reciver->text().length())
    {
        QMessageBox::critical(nullptr, "Reciver is Empty", "Reciver field can not be empty");
        return;
    }
    if (!users.contains(ui->lineEdit_reciver->text()))
    {
        QMessageBox::critical(nullptr, "Wrong Reciver", "User <" + ui->lineEdit_reciver->text() + "> dosen't exists!");
        ui->lineEdit_reciver->clear();
        return;
    }
    Message new_message(ui->lineEdit_sender->text(), ui->lineEdit_reciver->text());
    if (ui->lineEdit_subject->text().length())
        new_message.setSubject(ui->lineEdit_subject->text());
    new_message.setText(ui->plainTextEdit->toPlainText());
    new_message.send();
    QMessageBox::information(nullptr, "Sent Successfully", "Message Sent Successfully\nTime: " + QDateTime::currentDateTime().toString("dd MMMM yyyy hh:mm:ss.zzz"));
    on_pushButton_backtodash_clicked();
}
