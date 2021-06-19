#include "editgroup.h"
#include "ui_editgroup.h"

editGroup::editGroup(QMap<QString, QStringList> *groups, const QString &gp, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::editGroup)
{
    this->groups = groups;
    QMap<QString, QStringList> books = Book::loadBooks();
    QStringList data;

    ui->setupUi(this);
    ui->lineEdit_gptitle->setText(gp);

    for (auto it = books.constBegin(); it != books.constEnd(); ++it)
        data << it.key() + " : " + it.value().at(0) + " (" + it.value().at(1) + ")";
    ui->listWidget->insertItems(0, data);

    for (int i = 0; i < groups->value(gp).size(); ++i)
    {
        QList <QListWidgetItem *> items = ui->listWidget->findItems(groups->value(gp).at(i), Qt::MatchStartsWith);
        for (const auto &it : items)
            it->setSelected(true);
    }
}

editGroup::~editGroup()
{
    delete ui;
}

void editGroup::on_pushButton_save_clicked()
{
    QList<QListWidgetItem *> books = ui->listWidget->selectedItems();

    if (!books.size())
    {
        QMessageBox::critical(nullptr, "No Book Selected", "Please Select at least 1 book to add to this group");
        return;
    }

    QStringList add;
    for (int i = 0; i < books.size(); ++i)
    {
        QStringList tmp = books.at(i)->text().split(":");
        add << tmp.at(0).trimmed();
    }

    groups->insert(ui->lineEdit_gptitle->text(), add);

    if (group_item::saveChanges(groups))
        QMessageBox::information(nullptr, "Edited Successfully", ui->lineEdit_gptitle->text() + " Edited Successfully\nPlease Refresh The Table");

    this->close();
    delete this;
}
