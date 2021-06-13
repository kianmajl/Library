#ifndef BOOK_ITEM_H
#define BOOK_ITEM_H

#include "book.h"
#include "message.h"
#include "QDate"

#define MAX_DAYS 7

class book_item : public Book
{
public:
    book_item();
    static QMap<QPair<QString, QString>, QDate> loadData_issuedBooks();
    static bool saveChanges_issuedBooks(QMap<QPair<QString, QString>, QDate> &data);
    static void sendMessage(QString user);
    static int numIssued();
    static int numIssued(QString user);
    static void deleteBooks(QString isbn); // delete issue records of deleted book
    static void deleteUsers(QString user); // delete issue records of deleted user

private:
    QString user;
    QString isbn;
    QDate issue_date;
};

#endif // BOOK_ITEM_H
