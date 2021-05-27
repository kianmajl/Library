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
    ~MainWindow_user();

private:
    Ui::MainWindow_user *ui;
};

#endif // MAINWINDOW_USER_H
