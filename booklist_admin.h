#ifndef BOOKLIST_ADMIN_H
#define BOOKLIST_ADMIN_H

#include "book_item.h"
#include "group_item.h"
#include "addbook.h"
#include "editbook.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include <QWidget>
#include <QCompleter>

namespace Ui {
class BookList_Admin;
}

class BookList_Admin : public QWidget
{
    Q_OBJECT

public:
    explicit BookList_Admin(Ui::MainWindow *ui_dash, QWidget *dash, QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    int loadData();
    ~BookList_Admin();

private slots:
    void on_pushButton_backtodash_clicked();

    void on_pushButton_refresh_clicked();

    void on_pushButton_add_clicked();

    void on_pushButton_delete_clicked();

    void on_lineEdit_search_textChanged(const QString &arg1);

    void on_comboBox_search_currentIndexChanged(int index);

    void on_pushButton_edit_clicked();

private:
    Ui::BookList_Admin *ui;
    QWidget *admin_dash;
    Ui::MainWindow *ui_admindash;
    QPointF oldPos; // for draggable
    QMap <QString, QStringList> booksdb;
    QVector<QCompleter *> completer;
    bool change;
};

#endif // BOOKLIST_ADMIN_H
