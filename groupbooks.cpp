#include "groupbooks.h"
#include "ui_groupbooks.h"

#define GROUP_FILE "groupdb.txt"

groupBooks::groupBooks(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::groupBooks)
{
    ui->setupUi(this);
    this->LoadData();
}

void groupBooks::LoadData()
{
    QFile group_data(GROUP_FILE);

    if (!group_data.open(QIODevice::ReadWrite | QIODevice::Text))
        return;

    QTextStream in(&group_data);

    while (!in.atEnd())
        data << in.readLine();

    ui->listWidget->addItems(data);
    QCompleter *completer = new QCompleter(data, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->lineEdit->setCompleter(completer);

    group_data.close();
}

groupBooks::~groupBooks()
{
    delete ui;
}
