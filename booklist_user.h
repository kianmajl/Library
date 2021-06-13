#ifndef BOOKLIST_USER_H
#define BOOKLIST_USER_H

#include "book_item.h"
#include "book.h"
#include "ui_mainwindow_user.h"
#include <QWidget>
#include <QCompleter>
#include <QMouseEvent>
#include <QMessageBox>

namespace Ui {
class booklist_user;
}

class booklist_user : public QWidget
{
    Q_OBJECT

public:
    explicit booklist_user(const QString &user, Ui::MainWindow_user *ui_user_dash, QWidget *dash, QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    int loadData();
    ~booklist_user();

private slots:
    void on_lineEdit_search_textChanged(const QString &arg1);

    void on_comboBox_search_currentIndexChanged(int index);

    void on_pushButton_backtodash_clicked();

    void on_pushButton_issue_clicked();

    void on_pushButton_refresh_clicked();

private:
    Ui::booklist_user *ui;
    Ui::MainWindow_user *ui_user_dash;
    QWidget *user_dash;
    QPointF oldPos; // for draggable
    QString user;
    QMap <QString, QStringList> booksdb;
    QMap<QPair<QString, QString>, QDate> issuedbooksdb;
    QVector<QCompleter *> completer;
    bool change;
    int j;
};

#endif // BOOKLIST_USER_H
