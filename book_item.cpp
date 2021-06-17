#include "book_item.h"

#define RESERVE_FILE "reservedb.txt"
#define SEP_DATA ","
#define DATE_FORMAT "yyyyMMdd"

book_item::book_item()
{

}

QMap<QPair<QString, QString>, QDate> book_item::loadData_issuedBooks()
{
    QMap<QPair<QString, QString>, QDate> data;
    QFile reserve_file(RESERVE_FILE);
    QTextStream in(&reserve_file);

    reserve_file.open(QIODevice::ReadOnly | QIODevice::Text);

    while (!in.atEnd())
    {
        QStringList qsl = in.readLine().split(SEP_DATA);
        data[qMakePair(qsl.at(0), qsl.at(1))] = QDate::fromString(qsl.at(2), DATE_FORMAT);
    }

    reserve_file.close();
    return data;
}

bool book_item::saveChanges_issuedBooks(QMap<QPair<QString, QString>, QDate> &data)
{
    QFile reserve_file(RESERVE_FILE);

    if (!reserve_file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&reserve_file);
    for (auto it = data.constBegin(); it != data.constEnd(); ++it)
        out << it.key().first << SEP_DATA << it.key().second << SEP_DATA << it.value().toString(DATE_FORMAT) << "\n";
    reserve_file.close();
    return true;
}

void book_item::sendMessage(const QString &user)
{
    QDate currentDate = QDate::currentDate();
    QMap<QPair<QString, QString>, QDate> data = loadData_issuedBooks();

    for (auto it = data.constBegin(); it != data.constEnd(); ++it)
    {
        if (it.key().second == user)
        {
            QDate expire_date = it.value().addDays(MAX_DAYS);
            qint64 d = currentDate.daysTo(expire_date);
            if (d < 4 && d > -1 && !Message::isSend(currentDate.toString(DATE_FORMAT), user, it.key().first))
            {
                Message ex_date_close("SYSTEM", user);
                ex_date_close.setSubject("Expiration Date is close");
                ex_date_close.setText("Hi " + user + ";\nOnly " + QString::number(d) + " days left to expire date of " + it.key().first);
                ex_date_close.send();
            }

            else if (d < 0 && !Message::isSend(currentDate.toString(DATE_FORMAT), user, it.key().first))
            {
                Message ex_date_close("SYSTEM", user);
                ex_date_close.setSubject("Expiry date has passed");
                ex_date_close.setText("Hi " + user + ";\nExpiry date of " + it.key().first + " has passed\nPlease Return it !!!!");
                ex_date_close.send();
            }
        }
    }
}

int book_item::numIssued()
{
    int cnt = 0;
    QFile reserve_file(RESERVE_FILE);
    QTextStream in(&reserve_file);

    if (!reserve_file.open(QIODevice::ReadOnly | QIODevice::Text))
        return cnt;

    while (!in.atEnd())
    {
        in.readLine();
        ++cnt;
    }

    reserve_file.close();
    return cnt;
}

int book_item::numIssued(const QString &user)
{
    int cnt = 0;
    QFile reserve_file(RESERVE_FILE);
    QTextStream in(&reserve_file);

    if (!reserve_file.open(QIODevice::ReadOnly | QIODevice::Text))
        return cnt;

    while (!in.atEnd())
    {
        QStringList tmp = in.readLine().split(SEP_DATA);
        if (tmp.at(1) == user)
            ++cnt;
    }

    reserve_file.close();
    return cnt;
}

bool book_item::haveExpire(const QString &user)
{
    QDate current = QDate::currentDate();
    QMap<QPair<QString, QString>, QDate> data = loadData_issuedBooks();

    for (auto it = data.constBegin(); it != data.constEnd(); ++it)
    {
        QDate exp = it.value().addDays(MAX_DAYS);
        if (it.key().second == user && current.daysTo(exp) < 0)
            return true;
    }

    return false;
}

void book_item::deleteBooks(const QString &isbn)
{
    QMap<QPair<QString, QString>, QDate> data = loadData_issuedBooks();

    for (auto it = data.constBegin(); it != data.constEnd();)
    {
        if (it.key().first == isbn)
            data.erase(it++);
        else
            ++it;
    }

    saveChanges_issuedBooks(data);
}

void book_item::deleteUsers(const QString &user)
{
    QMap<QPair<QString, QString>, QDate> data = loadData_issuedBooks();

    for (auto it = data.constBegin(); it != data.constEnd();)
    {
        if (it.key().second == user)
            data.erase(it++);
        else
            ++it;
    }

    saveChanges_issuedBooks(data);
}
