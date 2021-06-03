#ifndef MAINWINDOW_USER_H
#define MAINWINDOW_USER_H

#include "authentication.h"
#include "compose.h"
#include <QMainWindow>
#include <QMouseEvent>
#include <QDateTime>

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

private:
    Ui::MainWindow_user *ui;
    QVector<QPair<QString, QWidget *>> forms;
    QPointF oldPos; // for draggable
    QString user; // logged in user
};

#endif // MAINWINDOW_USER_H
