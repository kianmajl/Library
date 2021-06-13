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
    explicit addGroup(QWidget *parent = nullptr);
    ~addGroup();

private slots:
    void on_pushButton_add_clicked();

private:
    Ui::addGroup *ui;
};

#endif // ADDGROUP_H
