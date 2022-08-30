#include "edit_user_data.h"
#include "ui_edit_user_data.h"

Edit_User_Data::Edit_User_Data(QMap<QString, QStringList> *data, const QString &user_selected, const bool &admin, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Edit_User_Data)
{
    this->data = data;
    this->user_selected = user_selected;
    this->admin = admin;
    ui->setupUi(this);
    ui->lineEdit_user->setText(user_selected);
    ui->lineEdit_pass->setText(data->value(user_selected).at(0));
    ui->radioButton_male->setChecked((data->value(user_selected).at(1).toInt()) ? false : true);
    ui->radioButton_female->setChecked((data->value(user_selected).at(1).toInt()) ? true : false);
    ui->checkBox_admin->setChecked(data->value(user_selected).at(2).toInt());
    if (user_selected == "admin")
        ui->checkBox_admin->setEnabled(false);
    if (!admin)
    {
        ui->label_isAdmin->hide();
        ui->label_sex->hide();
        ui->radioButton_female->hide();
        ui->radioButton_male->hide();
        ui->checkBox_admin->hide();
    }
}

Edit_User_Data::Edit_User_Data(const QString &user_selected, const bool &admin, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Edit_User_Data)
{
    users = User::LoadUsers();
    this->data = &users;
    this->user_selected = user_selected;
    this->admin = admin;
    ui->setupUi(this);
    ui->lineEdit_user->setText(user_selected);
    ui->lineEdit_pass->setText(data->value(user_selected).at(0));
    ui->radioButton_male->setChecked((data->value(user_selected).at(1).toInt()) ? false : true);
    ui->radioButton_female->setChecked((data->value(user_selected).at(1).toInt()) ? true : false);
    ui->checkBox_admin->setChecked(data->value(user_selected).at(2).toInt());
    if (user_selected == "admin")
        ui->checkBox_admin->setEnabled(false);
    if (!admin)
    {
        ui->label_isAdmin->hide();
        ui->label_sex->hide();
        ui->radioButton_female->hide();
        ui->radioButton_male->hide();
        ui->checkBox_admin->hide();
    }
}

Edit_User_Data::~Edit_User_Data()
{
    delete ui;
}

void Edit_User_Data::on_pushButton_save_clicked()
{
    QString pass = ui->lineEdit_pass->text();

    if (!pass.length())
    {
        QMessageBox::critical(nullptr, "Password is Empty", "Password can not be empty!");
        return;
    }

    QString hashed_pass;

    if (pass == data->value(user_selected).at(0)) // Check if password have change ?
        hashed_pass = pass;
    else
        hashed_pass = QString(QCryptographicHash::hash((pass.toLocal8Bit()), QCryptographicHash::Sha256).toHex());

    bool sex = (ui->radioButton_female->isChecked()) ? true : false;
    QStringList qsl;
    qsl << hashed_pass << QString::number(sex) << QString::number(ui->checkBox_admin->isChecked());
    data->insert(user_selected, qsl);
    if (User::SaveUsers(data))
        QMessageBox::information(nullptr, "Edited Successfully", user_selected + " Edited Successfully");
    this->close();
    delete this;
}
