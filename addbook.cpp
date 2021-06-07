#include "addbook.h"
#include "ui_addbook.h"

addBook::addBook(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addBook)
{
    ui->setupUi(this);
}

addBook::~addBook()
{
    delete ui;
}
