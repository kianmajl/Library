#include "authentication.h"
#include "ui_authentication.h"
#include "user.h"

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
    QString hashed_pass = QString(QCryptographicHash::hash((ui->lineEdit_pass->text().toLocal8Bit()), QCryptographicHash::Sha256).toHex());
    QString login_res = User::Login(username, hashed_pass);

    if (login_res == "ok")
    {
        QMessageBox::information(nullptr, "Hi", "test\t" + username);
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
    QString hashed_pass = QString(QCryptographicHash::hash((ui->lineEdit_pass->text().toLocal8Bit()), QCryptographicHash::Sha256).toHex());
    bool checkAdmin = ui->checkBox_admin->isChecked();

    QString register_res = User::Register(username, hashed_pass, checkAdmin);

    if (register_res == "ok")
    {
        QMessageBox::information(nullptr, "Hi", "test\t" + username);
    }
    else
    {
        QMessageBox::critical(nullptr, "Register Failed", register_res);
        ui->lineEdit_user->clear();
        ui->lineEdit_pass->clear();
        ui->checkBox_admin->setChecked(false);
    }
}
