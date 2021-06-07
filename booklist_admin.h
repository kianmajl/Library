#ifndef BOOKLIST_ADMIN_H
#define BOOKLIST_ADMIN_H

#include <QWidget>

namespace Ui {
class BookList_Admin;
}

class BookList_Admin : public QWidget
{
    Q_OBJECT

public:
    explicit BookList_Admin(QWidget *dash, QWidget *parent = nullptr);
    ~BookList_Admin();

private:
    Ui::BookList_Admin *ui;
    QWidget *admin_dash;
};

#endif // BOOKLIST_ADMIN_H
