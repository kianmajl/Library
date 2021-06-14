#include "mainwindow_user.h"
#include "ui_mainwindow_user.h"

#define AUTHENTICATION_FORM "auth"
#define INBOX_FORM "inbox"
#define OUTBOX_FORM "outbox"
#define BOOK_LIST_FORM "booklist"
#define RETURN_BOOK_FORM "returnb"
#define GROUP_LIST_FORM "grouplist"

MainWindow_user::MainWindow_user(QWidget *auth, QString user_logged_in, bool sex, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow_user)
{
    forms.append(qMakePair(AUTHENTICATION_FORM, auth));
    ui->setupUi(this);
    this->user = user_logged_in;
    ui->label_username->setText("Hi " + this->user);
    ui->label->setText("User Dashboard | " + QDate::currentDate().toString("dddd, MMMM dd, yyyy"));
    ui->frame_2->setStyleSheet((sex) ? "image: url(:/icons/icons/reading.png);" : "image: url(:/icons/icons/reading-m.png);");
    ui->pushButton_totalbissued->setText("Total Books Issued : " + QString::number(book_item::numIssued(user)));
    int unread_messages = Message::numUnreadMessages(user);
    if (unread_messages)
        ui->statusbar->showMessage("You Have " + QString::number(unread_messages) + " Unread Messages");
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

void MainWindow_user::on_pushButton_inbox_clicked()
{
    this->hide();
    QWidget * inb = searchForms(INBOX_FORM);
    if (!inb)
    {
        inbox *inb_frm = new inbox(ui, user, false, this);
        inb_frm->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
        forms.append(qMakePair(INBOX_FORM, inb_frm));
        inb = inb_frm;
    }
    inb->show();
}

void MainWindow_user::on_pushButton_outbox_clicked()
{
    this->hide();
    QWidget * out = searchForms(OUTBOX_FORM);
    if (!out)
    {
        outbox *out_frm = new outbox(this, user);
        out_frm->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
        forms.append(qMakePair(OUTBOX_FORM, out_frm));
        out = out_frm;
    }
    out->show();
}

void MainWindow_user::on_pushButton_viewlist_clicked()
{
    this->hide();
    QWidget *ba_list = searchForms(BOOK_LIST_FORM);
    if (!ba_list)
    {
        booklist_user *blu = new booklist_user(user, ui, this);
        blu->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
        forms.append(qMakePair(BOOK_LIST_FORM, blu));
        ba_list = blu;
    }
    ba_list->show();
}

void MainWindow_user::on_pushButton_returnbook_clicked()
{
    this->hide();
    QWidget *reb_list = searchForms(RETURN_BOOK_FORM);
    if (!reb_list)
    {
        returnBook *rb = new returnBook(ui, user, this);
        rb->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
        forms.append(qMakePair(RETURN_BOOK_FORM, rb));
        reb_list = rb;
    }
    reb_list->show();
}

void MainWindow_user::on_pushButton_viewgplist_clicked()
{
    this->hide();
    QWidget * gp_list = searchForms(GROUP_LIST_FORM);
    if (!gp_list)
    {
        groupBooks *gp = new groupBooks(this, false);
        gp->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
        forms.append(qMakePair(GROUP_LIST_FORM, gp));
        gp_list = gp;
    }
    gp_list->show();
}
