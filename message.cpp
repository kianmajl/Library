#include "message.h"

#define MESSAGE_FILE "message.txt"
#define SEP_DATA ","

void Message::send()
{
    QFile message(MESSAGE_FILE);
    QTextStream out(&message);

    if (!message.open(QIODevice::Append | QIODevice::Text))
        return;

    out << this->toString();
    message.close();
}

void Message::setSubject(const QString &subject)
{
    this->subject = subject;
}

void Message::setText(const QString &text)
{
    this->text = text;
}

Message::Message(const QString &sender, const QString &receiver)
{
    this->code = QDateTime::currentDateTime().toString("yyyyMMddhhmmsszzz");
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
    return qsl.join(SEP_DATA) + "/";
}

QMap<QString, QStringList> Message::loadMessages()
{
    QMap<QString, QStringList> msgdb;
    QFile msgdata(MESSAGE_FILE);
    QTextStream in(&msgdata);
    msgdata.open(QIODevice::ReadOnly | QIODevice::Text);

    QStringList allmsg = in.readAll().split("/");

    for (auto it = allmsg.constBegin(); it != allmsg.constEnd(); ++it)
    {
        QStringList msg = it->split(SEP_DATA);
        if (!msg[0].length())
            break;
        for (int i = 1; i < msg.size(); ++i)
            msgdb[msg[0]] << msg.at(i);
    }

    msgdata.close();
    return msgdb;
}

bool Message::saveChanges(QMap<QString, QStringList> &data)
{
    QFile new_data(MESSAGE_FILE);
    QTextStream out(&new_data);

    if (!new_data.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;
    for (auto it = data.constBegin(); it != data.constEnd(); ++it)
        out << it.key() << SEP_DATA << it.value().join(SEP_DATA) << "/";

    new_data.close();
    return true;
}

void Message::deleteMessages(const QString &username)
{
    QMap<QString, QStringList> msgdb = loadMessages();

    for (auto it = msgdb.constBegin(); it != msgdb.constEnd();)
    {
        if (it.value().at(1) == username)
            msgdb.erase(it++);
        else
            ++it;
    }
    saveChanges(msgdb);
}

int Message::numUnreadMessages(const QString &username)
{
    int cnt = 0;
    QFile message(MESSAGE_FILE);
    QTextStream in(&message);

    if (!message.open(QIODevice::ReadOnly | QIODevice::Text))
        return cnt;

    QStringList messages = in.readAll().split("/");

    for (auto it = messages.constBegin(); it != messages.constEnd(); ++it)
    {
        QStringList msg = it->split(SEP_DATA);

        if (!msg[0].length())
            break;
        if (msg[2] == username && !msg[5].toInt())
            cnt++;
    }

    message.close();
    return cnt;
}

bool Message::isSend(const QString &date, const QString &receiver, QString book_isbn, QString sender)
{
    QMap<QString, QStringList> msgdb = loadMessages();

    for (auto it = msgdb.constBegin(); it != msgdb.constEnd(); ++it)
    {
        if (it.key().startsWith(date) && it.value().at(0) == sender && it.value().at(1) == receiver && it.value().at(3).contains(book_isbn))
            return true;
    }

    return false;
}
