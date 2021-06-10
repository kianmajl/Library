#include "booklist_user.h"
#include "ui_booklist_user.h"

booklist_user::booklist_user(QWidget *dash, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::booklist_user)
{
    this->user_dash = dash;
    ui->setupUi(this);
}

booklist_user::~booklist_user()
{
    delete ui;
}
