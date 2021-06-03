#ifndef EDIT_USER_DATA_H
#define EDIT_USER_DATA_H

#include <QWidget>
#include <QMap>
#include <QString>
#include <QStringList>
#include <QCryptographicHash>
#include <QMessageBox>

namespace Ui {
class Edit_User_Data;
}

class Edit_User_Data : public QWidget
{
    Q_OBJECT

public:
    Edit_User_Data(QString user_selected, QMap<QString, QStringList> * data, QWidget *parent = nullptr);
    ~Edit_User_Data();

private slots:
    void on_pushButton_save_clicked();

private:
    Ui::Edit_User_Data *ui;
    QString user_selected;
    QMap<QString, QStringList> * data;
};

#endif // EDIT_USER_DATA_H
