#ifndef ADDGROUP_H
#define ADDGROUP_H

#include <QWidget>
#include <QMessageBox>
#include "editgroup.h"
#include "book.h"
#include "group_item.h"

namespace Ui {
class addGroup;
}

class addGroup : public QWidget
{
    Q_OBJECT

public:
    explicit addGroup(QMap<QString, QStringList> *groups, QMap<QString, QStringList> *books, QWidget *parent = nullptr);
    ~addGroup();

private slots:
    void on_pushButton_add_clicked();

private:
    Ui::addGroup *ui;
    QMap<QString, QStringList> *groups;
    QMap<QString, QStringList> *books;
};

#endif // ADDGROUP_H
