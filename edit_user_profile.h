#ifndef EDIT_USER_PROFILE_H
#define EDIT_USER_PROFILE_H

#include <QWidget>
#include <QTableWidgetItem>
#include <QTableWidget>
#include <QMouseEvent>
#include <QFile>
#include <QTextStream>
#include <QCompleter>
#include <QMessageBox>
#include "edit_user_data.h"
#include "ui_mainwindow.h"
#include "user.h"
#include "message.h"

namespace Ui {
class Edit_User_profile;
}

class Edit_User_profile : public QWidget
{
    Q_OBJECT

public:
    explicit Edit_User_profile(Ui::MainWindow *uiMainWindow, QWidget *admin_dash, QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    int LoadData();
    bool saveChanges();
    ~Edit_User_profile();

private slots:
    void on_pushButton_backtodash_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButton_edit_clicked();

    void on_pushButton_delete_clicked();

    void on_pushButton_Refresh_clicked();

private:
    Ui::Edit_User_profile *ui;
    Ui::MainWindow *uiMainWindow;
    QWidget *admin_dash; // pointer of admin dashboard
    QPointF oldPos; // for draggable
    QMap<QString, QStringList> user_data;
    bool change;
};

#endif // EDIT_USER_PROFILE_H
