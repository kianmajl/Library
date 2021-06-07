#include "outbox.h"
#include "ui_outbox.h"

outbox::outbox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::outbox)
{
    ui->setupUi(this);
}

outbox::~outbox()
{
    delete ui;
}
