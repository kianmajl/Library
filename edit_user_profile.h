#ifndef EDIT_USER_PROFILE_H
#define EDIT_USER_PROFILE_H

#include <QWidget>
#include <QTableWidgetItem>
#include <QMouseEvent>
#include <QFile>
#include <QTextStream>
#include <QCompleter>

namespace Ui {
class Edit_User_profile;
}

class Edit_User_profile : public QWidget
{
    Q_OBJECT

public:
    explicit Edit_User_profile(QWidget *admin_dash, QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    int LoadData();
    ~Edit_User_profile();

private slots:
    void on_pushButton_backtodash_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_tableWidget_currentCellChanged(int currentRow);

private:
    Ui::Edit_User_profile *ui;
    QWidget *admin_dash; // pointer of admin dashboard
    QPointF oldPos; // for draggable
    QMap<QString, QStringList> user_data;
};

#endif // EDIT_USER_PROFILE_H
