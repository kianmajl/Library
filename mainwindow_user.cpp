#include "mainwindow_user.h"
#include "ui_mainwindow_user.h"

MainWindow_user::MainWindow_user(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow_user)
{
    ui->setupUi(this);
}

MainWindow_user::~MainWindow_user()
{
    delete ui;
}
