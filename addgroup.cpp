#include "addgroup.h"
#include "ui_addgroup.h"

addGroup::addGroup(QMap<QString, QStringList> *groups, QMap<QString, QStringList> *books, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addGroup)
{
    this->books = books;
    this->groups = groups;
    QStringList data;
    ui->setupUi(this);
    for (auto it = books->constBegin(); it != books->constEnd(); ++it) // fill books list
        data << it.key() + " : " + it.value().at(0) + " (" + it.value().at(1) + ")";
    ui->listWidget->insertItems(0, data);
}

addGroup::~addGroup()
{
    delete ui;
}

void addGroup::on_pushButton_add_clicked()
{
    if (groups->contains(ui->lineEdit_gptitle->text()))
    {
        int ret = QMessageBox::warning(nullptr, "Error", "This group already exists\nDo you want to edit this group?", QMessageBox::Yes | QMessageBox::No);

        if (ret == QMessageBox::Yes)
        {
            editGroup *eg = new editGroup(groups, ui->lineEdit_gptitle->text());
            eg->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
            eg->show();

            this->close();
            delete this;
        }

        else
            ui->lineEdit_gptitle->clear();

        return;
    }

    QList<QListWidgetItem *> books = ui->listWidget->selectedItems();

    if (!books.size())
    {
        QMessageBox::critical(nullptr, "No Book Selected", "Please select at least 1 book to add to this group");
        return;
    }

    QStringList add; // ISBN's data
    for (int i = 0; i < books.size(); ++i)
    {
        QStringList tmp = books.at(i)->text().split(":");
        add << tmp.at(0).trimmed();
    }

    groups->insert(ui->lineEdit_gptitle->text(), add);

    if (group_item::saveChanges(groups))
        QMessageBox::information(nullptr, "Added Successfully", ui->lineEdit_gptitle->text() + " was successfully added\nPlease Refresh The Table");

    this->close();
    delete this;
}
