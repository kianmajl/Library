#include "mainwindow_user.h"
#include "ui_mainwindow_user.h"

MainWindow_user::MainWindow_user(QString user_logged_in, bool sex, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow_user)
{
    ui->setupUi(this);
    this->user = user_logged_in;
    ui->label_username->setText("Hi " + this->user);
    ui->label->setText("User Dashboard | " + QDateTime::currentDateTime().toString("dddd, MMMM dd, yyyy"));
    ui->frame_2->setStyleSheet((sex) ? "image: url(:/icons/icons/reading.png);" : "image: url(:/icons/icons/reading-m.png);");
}

void MainWindow_user::mousePressEvent(QMouseEvent *event)
{
    oldPos = event->globalPosition();
}

void MainWindow_user::mouseMoveEvent(QMouseEvent *event)
{
    const QPointF delta = event->globalPosition() - oldPos;
    move(x()+delta.x(), y()+delta.y());
    oldPos = event->globalPosition();
}

QString MainWindow_user::getUser()
{
    return this->user;
}

MainWindow_user::~MainWindow_user()
{
    delete ui;
}

void MainWindow_user::on_pushButton_logout_clicked()
{
    int ret = QMessageBox::question(nullptr, "Confirm Logout", "Are you sure you want to logout?");

    if (ret == QMessageBox::Yes)
    {
        authentication * auth = new authentication();
        this->close();
        auth->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
        auth->show();
    }
}
