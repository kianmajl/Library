#include "message.h"

#define MESSAGE_FILE "message.txt"
#define SEP_DATA ","

void Message::send()
{
    QFile message(MESSAGE_FILE);
    QTextStream out(&message);

    if (!message.open(QIODevice::Append | QIODevice::Text))
        return;

    out << toString();
    message.close();
}

void Message::setSubject(QString subject)
{
    this->subject = subject;
}

void Message::setText(QString text)
{
    this->text = text;
}

Message::Message(QString sender, QString receiver)
{
    this->code = QDateTime::currentDateTime().toString("yyMMddhhmmss");
    this->isRead = false;
    this->sender = sender;
    this->receiver = receiver;
    this->subject = "No Subject";
    this->text = "";
}

QString Message::toString()
{
    QStringList qsl;
    qsl << this->code << this->sender << this->receiver << this->subject << this->text << QString::number(this->isRead);
    return qsl.join(SEP_DATA) + "-";
}

int Message::numUnreadMessages(QString username)
{
    int cnt = 0;
    QFile message(MESSAGE_FILE);
    QTextStream in(&message);

    if (!message.open(QIODevice::ReadOnly | QIODevice::Text))
        return cnt;

    QStringList messages = in.readAll().split("-");

    for (auto it = messages.constBegin(); it != messages.constEnd(); ++it)
    {
        QStringList msg = it->split(SEP_DATA);
        if (msg[2] == username && !msg[4].toInt())
            cnt++;
    }

    return cnt;
}
