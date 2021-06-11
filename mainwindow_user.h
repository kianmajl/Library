#ifndef MAINWINDOW_USER_H
#define MAINWINDOW_USER_H

#include "authentication.h"
#include "compose.h"
#include "edit_user_data.h"
#include "user.h"
#include "message.h"
#include "inbox.h"
#include "outbox.h"
#include "booklist_user.h"
#include <QMainWindow>
#include <QMouseEvent>
#include <QDate>

namespace Ui {
class MainWindow_user;
}

class MainWindow_user : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow_user(QWidget *auth, QString user_logged_in, bool sex, QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    QWidget *searchForms(QString name);
    void deleteForms();
    ~MainWindow_user();

private slots:
    void on_pushButton_logout_clicked();

    void on_pushButton_compose_clicked();

    void on_pushButton_editprofile_clicked();

    void on_pushButton_inbox_clicked();

    void on_pushButton_outbox_clicked();

    void on_pushButton_viewlist_clicked();

private:
    Ui::MainWindow_user *ui;
    QVector<QPair<QString, QWidget *>> forms;
    QPointF oldPos; // for draggable
    QString user; // logged in user
};

#endif // MAINWINDOW_USER_H
