#include "mainwindow.h"
#include "ui_mainwindow.h"

#define GROUP_LIST_FORM "grouplist"
#define ISSUED_BOOK_LIST_FORM "isbooklist"
#define BOOK_LIST_FORM "booklist"
#define USERS_LIST_FORM "userlist"
#define AUTHENTICATION_FORM "auth"

MainWindow::MainWindow(QWidget *auth, QString user_logged_in, bool sex, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    forms.append(qMakePair(AUTHENTICATION_FORM, auth));
    ui->setupUi(this);
    this->user = user_logged_in;
    ui->label_username->setText("Hi " + this->user);
    ui->label->setText("Admin Dashboard | " + QDateTime::currentDateTime().toString("dddd, MMMM dd, yyyy"));
    ui->frame_2->setStyleSheet((sex) ? "image: url(:/icons/icons/librarian.png);" : "image: url(:/icons/icons/librarian-m.png);");
    setTotalUser();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    oldPos = event->globalPosition();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    const QPointF delta = event->globalPosition() - oldPos;
    move(x()+delta.x(), y()+delta.y());
    oldPos = event->globalPosition();
}

QWidget *MainWindow::searchForms(QString name)
{
    for (auto i = forms.constBegin(); i != forms.constEnd(); ++i)
        if (i->first == name)
            return i->second; // Pointer of form
    return nullptr;
}

void MainWindow::deleteForms()
{
    for (auto i = forms.begin(); i != forms.end(); ++i)
        if (i->first != AUTHENTICATION_FORM)
            delete i->second;
    forms.clear();
    delete this;
}

void MainWindow::setTotalUser()
{
    ui->pushButton_totaluser->setText("Total Users : " + QString::number(User::LoadData()));
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
        QWidget *aui = searchForms(AUTHENTICATION_FORM);
        this->close();
        aui->show();
        deleteForms();
    }
}

void MainWindow::on_pushButton_viewblist_clicked()
{

}

void MainWindow::on_pushButton_viewgrouplist_clicked()
{
    this->hide();
    QWidget * gp_list = searchForms(GROUP_LIST_FORM);
    if (!gp_list)
    {
        groupBooks *gp = new groupBooks(this);
        gp->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
        forms.append(qMakePair(GROUP_LIST_FORM, gp));
        gp_list = gp;
    }
    gp_list->show();
}

void MainWindow::on_pushButton_editprofile_clicked()
{
    this->hide();
    QWidget * us_list = searchForms(USERS_LIST_FORM);
    if (!us_list)
    {
        Edit_User_profile *eup = new Edit_User_profile(ui, this);
        eup->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
        forms.append(qMakePair(USERS_LIST_FORM, eup));
        us_list = eup;
    }
    us_list->show();
}
