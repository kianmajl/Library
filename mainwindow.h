#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "authentication.h"
#include "user.h"
#include "groupbooks.h"
#include "edit_user_profile.h"
#include <QMainWindow>
#include <QMouseEvent>
#include <QDateTime>
#include <QVector>
#include <QPair>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *auth, QString user_logged_in, bool sex, QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    QWidget *searchForms(QString name);
    void deleteForms();
    ~MainWindow();

private slots:
    void on_pushButton_logout_clicked();

    void on_pushButton_viewblist_clicked();

    void on_pushButton_viewgrouplist_clicked();

    void on_pushButton_editprofile_clicked();

private:
    Ui::MainWindow *ui;
    QVector<QPair<QString, QWidget *>> forms;
    QPointF oldPos; // for draggable
    QString user; // logged in user
};
#endif // MAINWINDOW_H
