#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QString user_logged_in, bool sex, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->user = user_logged_in;
    ui->label_username->setText("Hi " + this->user);
    ui->label->setText("Admin Dashboard | " + QDateTime::currentDateTime().toString("dddd, MMMM dd, yyyy"));
    ui->frame_2->setStyleSheet((sex) ? "image: url(:/icons/icons/librarian.png);" : "image: url(:/icons/icons/librarian-m.png);");
}

QString MainWindow::getUser()
{
    return this->user;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_logout_clicked()
{
    int ret = QMessageBox::question(nullptr, "Confirm Logout", "Are you sure you want to logout?");
    if (ret == QMessageBox::Yes)
    {
        authentication * aui = new authentication();
        this->close();
        aui->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
        aui->show();
    }
}

void MainWindow::on_pushButton_viewblist_clicked()
{

}

void MainWindow::on_pushButton_viewgrouplist_clicked()
{
    groupBooks * gp = new groupBooks();
    this->showMinimized();
    gp->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    gp->show();
}
