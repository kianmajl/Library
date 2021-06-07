#ifndef BOOKLIST_ADMIN_H
#define BOOKLIST_ADMIN_H

#include "book.h"
#include "addbook.h"
#include <QWidget>

namespace Ui {
class BookList_Admin;
}

class BookList_Admin : public QWidget
{
    Q_OBJECT

public:
    explicit BookList_Admin(QWidget *dash, QWidget *parent = nullptr);
    int loadData();
    ~BookList_Admin();

private slots:
    void on_pushButton_backtodash_clicked();

    void on_pushButton_refresh_clicked();

    void on_pushButton_add_clicked();

private:
    Ui::BookList_Admin *ui;
    QWidget *admin_dash;
    QMap <QString, QStringList> booksdb;
};

#endif // BOOKLIST_ADMIN_H
