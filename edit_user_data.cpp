#include "edit_user_data.h"
#include "ui_edit_user_data.h"

Edit_User_Data::Edit_User_Data(QString user_selected, QMap<QString, QStringList> &data, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Edit_User_Data)
{
    this->data = data;
    this->user_selected = user_selected;
    ui->setupUi(this);
    ui->lineEdit_user->setText(user_selected);
    ui->radioButton_male->setChecked((data[user_selected][1].toInt()) ? false : true);
    ui->radioButton_female->setChecked((data[user_selected][1].toInt()) ? true : false);
}

Edit_User_Data::~Edit_User_Data()
{
    delete ui;
}
