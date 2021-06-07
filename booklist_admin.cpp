#include "booklist_admin.h"
#include "ui_booklist_admin.h"

BookList_Admin::BookList_Admin(QWidget *dash, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BookList_Admin)
{
    this->admin_dash = dash;
    ui->setupUi(this);
}

BookList_Admin::~BookList_Admin()
{
    delete ui;
}
