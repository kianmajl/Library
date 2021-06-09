#ifndef INBOX_H
#define INBOX_H

#include <QWidget>
#include <QString>
#include <QStringList>
#include <QMap>
#include <QDateTime>
#include <QMessageBox>
#include "message.h"
#include "compose.h"
#include "ui_mainwindow.h"
#include "ui_mainwindow_user.h"

namespace Ui {
class inbox;
}

class inbox : public QWidget
{
    Q_OBJECT

public:
    explicit inbox(Ui::MainWindow *ui_admindash, QString user, bool isAdmin, QWidget *dash, QWidget *parent = nullptr);
    explicit inbox(Ui::MainWindow_user *ui_userdash, QString user, bool isAdmin, QWidget *dash, QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    int LoadData();
    bool saveChanges();
    ~inbox();

private slots:
    void on_pushButton_backtodash_clicked();

    void on_tableWidget_currentCellChanged(int currentRow);

    void on_pushButton_delete_clicked();

    void on_pushButton_asread_clicked();

    void on_pushButton_reply_clicked();

    void on_pushButton_forward_clicked();

private:
    Ui::inbox *ui;
    Ui::MainWindow *ui_admindash;
    Ui::MainWindow_user *ui_userdash;
    QWidget *dash;
    QPointF oldPos; // for draggable
    QString user;
    QMap<QString, QStringList> messages_data;
    bool change;
    bool isAdmin;
};

#endif // INBOX_H
