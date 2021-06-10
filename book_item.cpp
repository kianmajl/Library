#include "book_item.h"

#define RESERVE_FILE "reservedb.txt"
#define SEP_DATA ","
#define TIME_FORMAT "yyyyMMddhhmmss"

book_item::book_item()
{

}

QMap<QPair<QString, QString>, QDateTime> book_item::loadData()
{
    QMap<QPair<QString, QString>, QDateTime> data;
    QFile reserve_file(RESERVE_FILE);
    QTextStream in(&reserve_file);

    reserve_file.open(QIODevice::ReadOnly | QIODevice::Text);

    while (!in.atEnd())
    {
        QStringList qsl = in.readLine().split(SEP_DATA);
        data[qMakePair(qsl[0], qsl[1])] = QDateTime::fromString(TIME_FORMAT);
    }

    reserve_file.close();
    return data;
}

bool book_item::saveChanges(QMap<QPair<QString, QString>, QDateTime> &data)
{
    QFile reserve_file(RESERVE_FILE);

    if (!reserve_file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&reserve_file);
    for (auto it = data.constBegin(); it != data.constEnd(); ++it)
        out << it.key().first << SEP_DATA << it.key().second << SEP_DATA << it.value().toString(TIME_FORMAT) << "\n";
    reserve_file.close();
    return true;
}

void book_item::sendMessage(QString user)
{
    QDateTime currentDate = QDateTime::currentDateTime();
    QMap<QPair<QString, QString>, QDateTime> data;
}
