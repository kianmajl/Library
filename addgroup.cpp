#include "addgroup.h"
#include "ui_addgroup.h"

addGroup::addGroup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addGroup)
{
    QMap<QString, QStringList> books = Book::loadBooks();
    QStringList data;
    ui->setupUi(this);
    for (auto it = books.constBegin(); it != books.constEnd(); ++it)
        data << it.key() + " : " + it.value().at(0) + " (" + it.value().at(1) + ")";
    ui->listWidget->insertItems(0, data);
}

addGroup::~addGroup()
{
    delete ui;
}

void addGroup::on_pushButton_add_clicked()
{
    QMap<QString, QStringList> data = group_item::loadData();
    QList<QListWidgetItem *> books = ui->listWidget->selectedItems();

    for (int i = 0; i < books.size(); ++i)
    {
        QStringList tmp = books.at(i)->text().split(":");
        data[ui->lineEdit_gptitle->text()] << tmp[0].trimmed();
    }

    if (group_item::saveChanges(data))
        QMessageBox::information(nullptr, "Added Successfully", ui->lineEdit_gptitle->text() + " Added Successfully\nPlease Refresh The Table");

    this->close();
    delete this;
}
