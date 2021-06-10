#ifndef BOOK_ITEM_H
#define BOOK_ITEM_H

#include "book.h"
#include "message.h"
#include "QDateTime"

#define MAX_DAYS 7

class book_item : public Book
{
public:
    book_item();
    static QMap<QPair<QString, QString>, QDateTime> loadData();
    static bool saveChanges(QMap<QPair<QString, QString>, QDateTime> &data);
    static void sendMessage(QString user);

private:
    QString user;
    QString isbn;
    QDateTime issue_date;
};

#endif // BOOK_ITEM_H
