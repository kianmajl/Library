#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QString user_logged_in, bool sex, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_username->setText("Hi " + user_logged_in);
    ui->label->setText("Admin Dashboard | " + QDateTime::currentDateTime().toString("dddd, MMMM dd, yyyy"));
    ui->frame_2->setStyleSheet((sex) ? "image: url(:/icons/icons/librarian.png);" : "image: url(:/icons/icons/librarian-m.png);");
}

MainWindow::~MainWindow()
{
    delete ui;
}

