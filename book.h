#ifndef BOOK_H
#define BOOK_H

#include <QMap>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStringList>

class Book
{
public:
    Book();
    static bool saveChanges(QMap<QString, QStringList> *data);
    static QMap<QString, QStringList> loadBooks();
    static int numBooks();

private:
    QString ISBN;
    QString title;
    QString author;
    QString subject;
    QString publisher;
    QString language;
    int numberOfPages;
    int available;
};

#endif // BOOK_H
