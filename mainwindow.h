#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "authentication.h"
#include <QMainWindow>
#include <QDateTime>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QString user_logged_in, bool sex, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_logout_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
