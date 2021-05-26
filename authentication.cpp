#include "authentication.h"
#include "ui_authentication.h"
#include "user.h"
#include "mainwindow.h"

authentication::authentication(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::authentication)
{
    ui->setupUi(this);
}

authentication::~authentication()
{
    delete ui;
}

void authentication::on_pushButton_signin_clicked()
{
    QString username = ui->lineEdit_user->text();
    QString password = ui->lineEdit_pass->text();
    QString hashed_pass = QString(QCryptographicHash::hash((password.toLocal8Bit()), QCryptographicHash::Sha256).toHex());

    QString login_res = (username.length() && password.length()) ? User::Login(username, hashed_pass) : "Please complete the form";

    if (login_res == "ok_admin")
    {
        QMessageBox::information(nullptr, "Hi", login_res); // for testing
    }
    else if (login_res == "ok")
    {
        QMessageBox::information(nullptr, "Hi", login_res); // for testing
    }
    else
    {
        QMessageBox::critical(nullptr, "Login Failed", login_res);
        ui->lineEdit_user->clear();
        ui->lineEdit_pass->clear();
    }
}

void authentication::on_pushButton_signup_clicked()
{
    QString username = ui->lineEdit_user->text();
    QString password = ui->lineEdit_pass->text();
    QString hashed_pass = QString(QCryptographicHash::hash((password.toLocal8Bit()), QCryptographicHash::Sha256).toHex());
    bool checkAdmin = ui->checkBox_admin->isChecked();

    QString register_res = (username.length() && password.length()) ? User::Register(username, hashed_pass, checkAdmin) : "Please complete the form";

    if (register_res == "ok")
    {
        QMessageBox::information(nullptr, "Registered Successfully", "Thanks for signing up : " + username);
        authentication::on_pushButton_signin_clicked();
    }
    else
    {
        QMessageBox::critical(nullptr, "Register Failed", register_res);
        ui->lineEdit_user->clear();
        ui->lineEdit_pass->clear();
        ui->checkBox_admin->setChecked(false);
    }
}
