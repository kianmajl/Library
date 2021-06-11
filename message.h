#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>
#include <QDateTime>
#include <QFile>
#include <QDateTime>

class Message
{
public:
    void send();
    void setSubject(QString subject);
    void setText(QString text);
    Message(QString sender, QString receiver);
    QString toString();
    static QMap<QString, QStringList> loadMessages();
    static bool saveChanges(QMap<QString, QStringList> &data);
    static void deleteMessages(QString username);
    static int numUnreadMessages(QString username);
    static bool isSend(QString date, QString receiver, QString sender = "SYSTEM");

private:
    QString code;
    QString sender;
    QString receiver;
    QString subject;
    QString text;
    bool isRead;
};

#endif // MESSAGE_H
