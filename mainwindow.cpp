#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, QString user_logged_in)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusbar->showMessage("Welcome " + user_logged_in, 5000);
    ui->label_time->setText(QDateTime::currentDateTime().toString("dddd, MMMM dd, yyyy"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

