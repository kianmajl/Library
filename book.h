#ifndef BOOK_H
#define BOOK_H

#include <QString>

class Book
{
public:
    Book();

private:
    QString ISBN;
    QString title;
    QString author;
    QString subject;
    QString publisher;
    QString language;
    int numberOfPages;
};

#endif // BOOK_H
