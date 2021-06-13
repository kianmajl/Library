#ifndef EDITGROUP_H
#define EDITGROUP_H

#include <QWidget>
#include "group_item.h"
#include "book.h"

namespace Ui {
class editGroup;
}

class editGroup : public QWidget
{
    Q_OBJECT

public:
    explicit editGroup(QMap<QString, QStringList> * groups, const QString &gp, QWidget *parent = nullptr);
    ~editGroup();

private:
    Ui::editGroup *ui;
    QMap<QString, QStringList> * groups;
};

#endif // EDITGROUP_H
