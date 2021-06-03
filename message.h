#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>
#include <QDateTime>

class Message
{
public:
    Message();

private:
    QDateTime time_sent;
    QString code;
    QString sender;
    QString receiver;
    bool isRead;
};

#endif // MESSAGE_H
