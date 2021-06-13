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
    void setSubject(const QString &subject);
    void setText(const QString &text);
    Message(const QString &sender, const QString &receiver);
    QString toString();
    static QMap<QString, QStringList> loadMessages();
    static bool saveChanges(QMap<QString, QStringList> &data);
    static void deleteMessages(const QString &username);
    static int numUnreadMessages(const QString &username);
    static bool isSend(const QString &date, const QString &receiver, QString book_isbn = "", QString sender = "SYSTEM");

private:
    QString code;
    QString sender;
    QString receiver;
    QString subject;
    QString text;
    bool isRead;
};

#endif // MESSAGE_H
