#include "edit_user_data.h"
#include "ui_edit_user_data.h"

Edit_User_Data::Edit_User_Data(QString user_selected, QMap<QString, QStringList> * data, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Edit_User_Data)
{
    this->data = data;
    this->user_selected = user_selected;
    ui->setupUi(this);
    ui->lineEdit_user->setText(user_selected);
    ui->lineEdit_pass->setText(data->value(user_selected).at(0));
    ui->radioButton_male->setChecked((data->value(user_selected).at(1).toInt()) ? false : true);
    ui->radioButton_female->setChecked((data->value(user_selected).at(1).toInt()) ? true : false);
    ui->checkBox_admin->setChecked(data->value(user_selected).at(2).toInt());
    if (user_selected == "admin")
        ui->checkBox_admin->setEnabled(false);
}

Edit_User_Data::~Edit_User_Data()
{
    delete ui;
}

void Edit_User_Data::on_pushButton_save_clicked()
{
    QString pass = ui->lineEdit_pass->text();
    QString hashed_pass;

    if (pass == data->value(user_selected).at(0))
        hashed_pass = pass;
    else
        hashed_pass = QString(QCryptographicHash::hash((pass.toLocal8Bit()), QCryptographicHash::Sha256).toHex());

    bool sex = (ui->radioButton_female->isChecked()) ? true : false;
    QStringList qsl;
    qsl << hashed_pass << QString::number(sex) << QString::number(ui->checkBox_admin->isChecked());
    data->insert(user_selected, qsl);
    this->close();
    delete this;
}
