#include "groupbooks.h"
#include "ui_groupbooks.h"

#define GROUP_FILE "groupdb.txt"

groupBooks::groupBooks(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::groupBooks)
{
    ui->setupUi(this);
    int num_loaded_data = this->LoadData();
    ui->label->setText("Group Books | " + QString::number(num_loaded_data) + " Records Loaded");
}

int groupBooks::LoadData()
{
    QFile group_data(GROUP_FILE);

    if (!group_data.open(QIODevice::ReadOnly | QIODevice::Text))
        return 0;

    QTextStream in(&group_data);

    while (!in.atEnd())
        data << in.readLine();

    ui->listWidget->addItems(data);
    QCompleter *completer = new QCompleter(data, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->lineEdit->setCompleter(completer);

    group_data.close();
    return this->data.length();
}

groupBooks::~groupBooks()
{
    delete ui;
}

void groupBooks::on_lineEdit_textChanged(const QString &arg1)
{
    QList<QListWidgetItem *> qlwi = ui->listWidget->findItems(arg1, Qt::MatchExactly);
    for (const auto &i : qlwi)
        ui->listWidget->setCurrentItem(i);
}

void groupBooks::on_listWidget_currentTextChanged(const QString &currentText)
{
    ui->lineEdit->setText(currentText);
}
