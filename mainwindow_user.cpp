#include "mainwindow_user.h"
#include "ui_mainwindow_user.h"

#define AUTHENTICATION_FORM "auth"

MainWindow_user::MainWindow_user(QWidget *auth, QString user_logged_in, bool sex, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow_user)
{
    forms.append(qMakePair(AUTHENTICATION_FORM, auth));
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

QWidget *MainWindow_user::searchForms(QString name)
{
    for (auto i = forms.constBegin(); i != forms.constEnd(); ++i)
        if (i->first == name)
            return i->second; // Pointer of form
    return nullptr;
}

void MainWindow_user::deleteForms()
{
    for (auto i = forms.begin(); i != forms.end(); ++i)
        if (i->first != AUTHENTICATION_FORM)
            delete i->second;
    forms.clear();
    delete this;
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
        QWidget *aui = searchForms(AUTHENTICATION_FORM);
        this->close();
        aui->show();
        deleteForms();
    }
}

void MainWindow_user::on_pushButton_compose_clicked()
{
    Compose * cmp = new Compose(this, this->user);
    this->hide();
    cmp->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    cmp->show();
}

void MainWindow_user::on_pushButton_editprofile_clicked()
{
    Edit_User_Data *eud = new Edit_User_Data(this->user, false);
    eud->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
    eud->show();
}
