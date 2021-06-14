#include "group_item.h"

#define GROUP_FILE "groupdb.txt"
#define SEP_DATA ","

group_item::group_item()
{

}

QMap<QString, QStringList> group_item::loadData()
{
    QMap<QString, QStringList> data;
    QFile groupdb(GROUP_FILE);
    QTextStream in(&groupdb);
    groupdb.open(QIODevice::ReadOnly | QIODevice::Text);

    while (!in.atEnd())
    {
        QStringList tmp = in.readLine().split(SEP_DATA);
        for (int i = 1; i < tmp.size(); ++i)
            data[tmp.at(0)] << tmp.at(i);
    }

    groupdb.close();
    return data;
}

bool group_item::saveChanges(QMap<QString, QStringList> *data)
{
    QFile groupdb(GROUP_FILE);

    if (!groupdb.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&groupdb);
    for (auto it = data->constBegin(); it != data->constEnd(); ++it)
        out << it.key() << SEP_DATA << it.value().join(SEP_DATA) << "\n";

    groupdb.close();
    return true;
}

void group_item::deleteBook(const QString &isbn)
{
    QMap<QString, QStringList> data = loadData();

    for (auto it = data.constBegin(); it != data.constEnd(); ++it)
    {
        if (it.value().contains(isbn))
        {
            QStringList tmp = it.value();
            tmp.removeOne(isbn);
            data.insert(it.key(), tmp);
        }
    }

    saveChanges(&data);
}
