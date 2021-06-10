#ifndef BOOKLIST_USER_H
#define BOOKLIST_USER_H

#include "book.h"
#include <QWidget>
#include <QCompleter>

namespace Ui {
class booklist_user;
}

class booklist_user : public QWidget
{
    Q_OBJECT

public:
    explicit booklist_user(QWidget *dash, QWidget *parent = nullptr);
    ~booklist_user();

private:
    Ui::booklist_user *ui;
    QWidget *user_dash;
};

#endif // BOOKLIST_USER_H
