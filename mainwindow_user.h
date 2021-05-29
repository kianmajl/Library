#ifndef MAINWINDOW_USER_H
#define MAINWINDOW_USER_H

#include "authentication.h"
#include <QMainWindow>
#include <QDateTime>

namespace Ui {
class MainWindow_user;
}

class MainWindow_user : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow_user(QString user_logged_in, bool sex, QWidget *parent = nullptr);
    QString getUser();
    ~MainWindow_user();

private slots:
    void on_pushButton_logout_clicked();

private:
    Ui::MainWindow_user *ui;
    QString user;
};

#endif // MAINWINDOW_USER_H
