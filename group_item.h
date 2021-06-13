#ifndef GROUP_ITEM_H
#define GROUP_ITEM_H

#include <QString>
#include <QMap>
#include <QFile>
#include <QTextStream>

class group_item
{
public:
    group_item();
    static QMap<QString, QStringList> loadData();
    static bool saveChanges(QMap<QString, QStringList> *data);
};

#endif // GROUP_ITEM_H
