#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, QString user_logged_in)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_username->setText("Hi " + user_logged_in);
    ui->label_time->setText(QDateTime::currentDateTime().toString("dddd, MMMM dd, yyyy"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

