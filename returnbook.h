#ifndef RETURNBOOK_H
#define RETURNBOOK_H

#include <QCompleter>
#include <QMouseEvent>
#include <QWidget>
#include <QMessageBox>
#include "ui_mainwindow_user.h"
#include "book_item.h"

namespace Ui {
class returnBook;
}

class returnBook : public QWidget
{
    Q_OBJECT

public:
    explicit returnBook(Ui::MainWindow_user *ui_user_dash, QString user, QWidget *user_dash, QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    int loadData();
    ~returnBook();

private slots:
    void on_pushButton_refresh_clicked();

    void on_lineEdit_search_textChanged(const QString &arg1);

    void on_comboBox_search_currentIndexChanged(int index);

    void on_pushButton_backtodash_clicked();

    void on_pushButton_return_clicked();

private:
    Ui::returnBook *ui;
    Ui::MainWindow_user *ui_user_dash;
    QString user;
    QWidget *dash;
    QPointF oldPos; // for draggable
    QMap <QString, QStringList> booksdb;
    QMap<QPair<QString, QString>, QDate> issuedbooksdb;
    QVector<QCompleter *> completer;
    bool change;
    int j;
};

#endif // RETURNBOOK_H
