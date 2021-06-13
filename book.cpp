#include "book.h"

#define BOOK_FILE "bookdb.txt"
#define SEP_DATA ","

Book::Book()
{
}

bool Book::saveChanges(QMap<QString, QStringList> *data)
{
    QFile bookdb(BOOK_FILE);
    if (!bookdb.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;
    QTextStream out(&bookdb);

    for (auto it = data->constBegin(); it != data->constEnd(); ++it)
        out << it.key() << SEP_DATA << it.value().join(SEP_DATA) << "\n";

    bookdb.close();
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
            data[tmp.at(0)] << tmp.at(i);
    }

    bookdb.close();
    return data;
}

int Book::numBooks()
{
    int cnt = 0;
    QFile bookdb(BOOK_FILE);
    QTextStream in(&bookdb);

    if(!bookdb.open(QIODevice::ReadOnly | QIODevice::Text))
        return cnt;

    while (!in.atEnd())
    {
        in.readLine();
        ++cnt;
    }

    bookdb.close();
    return cnt;
}
