#include "authentication.h"
#include "ui_authentication.h"
#include "user.h"
#include "book_item.h"
#include "mainwindow.h"
#include "mainwindow_user.h"

authentication::authentication(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::authentication)
{
    ui->setupUi(this);
    // Create Admin User
    {
        QString usera = "admin";
        QString passa = QString(QCryptographicHash::hash((QString("admin").toLocal8Bit()), QCryptographicHash::Sha256).toHex());
        User::Register(usera, passa, false, true);
    }
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

    if (login_res == "ok_admin_m") // admin_male
    {
        MainWindow * mw_admin = new MainWindow(this, username, false);
        this->close();
        mw_admin->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
        mw_admin->show();
    }
    else if (login_res == "ok_admin_f") // admin_female
    {
        MainWindow * mw_admin = new MainWindow(this, username, true);
        this->close();
        mw_admin->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
        mw_admin->show();
    }
    else if (login_res == "ok_m") // user_male
    {
        book_item::sendMessage(username);
        MainWindow_user * mw_user = new MainWindow_user(this, username, false);
        this->close();
        mw_user->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
        mw_user->show();
    }
    else if (login_res == "ok_f") // user_female
    {
        book_item::sendMessage(username);
        MainWindow_user * mw_user = new MainWindow_user(this, username, true);
        this->close();
        mw_user->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
        mw_user->show();
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
    bool sex = (ui->radioButton_male->isChecked()) ? false : true;

    QString register_res = (username.length() && password.length() && (ui->radioButton_female->isChecked() || ui->radioButton_male->isChecked())) ? User::Register(username, hashed_pass, sex) : "Please complete the form";

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
        ui->radioButton_female->setChecked(false);
        ui->radioButton_male->setChecked(false);
    }
}
