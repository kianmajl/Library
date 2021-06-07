#include "book.h"

#define BOOK_FILE "bookdb.txt"
#define SEP_DATA ","

Book::Book(QString ISBN, QString title, QString author, QString subject, QString publisher, QString language, int nump, int available)
{
    this->ISBN = ISBN;
    this->title = title;
    this->author = author;
    this->subject = subject;
    this->publisher = publisher;
    this->language = language;
    this->numberOfPages = nump;
    this->available = available;
}

bool Book::saveChanges(QMap<QString, QStringList> &data)
{
    QFile bookdb(BOOK_FILE);
    if (!bookdb.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;
    QTextStream out(&bookdb);

    for (auto it = data.constBegin(); it != data.constEnd(); ++it)
        out << it.key() << SEP_DATA << it.value().join(SEP_DATA) << "\n";

    return true;
}

QMap<QString, QStringList> Book::loadBooks()
{
    QMap<QString, QStringList> data;
    QFile bookdb(BOOK_FILE);
    QTextStream in(&bookdb);

    bookdb.open(QIODevice::ReadOnly | QIODevice::Text);

    while (!in.atEnd())
    {
        QStringList tmp = in.readLine().split(SEP_DATA);
        for (int i = 1; i < tmp.size(); ++i)
            data[tmp[0]] << tmp.at(i);
    }

    bookdb.close();
    return data;
}
