#include "editgroup.h"
#include "ui_editgroup.h"

editGroup::editGroup(const QString &gp, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::editGroup)
{
    this->groups = group_item::loadData();
    QMap<QString, QStringList> books = Book::loadBooks();
    QStringList data;

    ui->setupUi(this);
    ui->lineEdit_gptitle->setText(gp);

    for (auto it = books.constBegin(); it != books.constEnd(); ++it)
        data << it.key() + " : " + it.value().at(0) + " (" + it.value().at(1) + ")";
    ui->listWidget->insertItems(0, data);

    for (int i = 0; i < groups.value(gp).size(); ++i)
    {
        QList <QListWidgetItem *> items = ui->listWidget->findItems(groups.value(gp).at(i), Qt::MatchExactly);
        for (const auto &it : items)
            it->setSelected(true);
    }
}

editGroup::~editGroup()
{
    delete ui;
}
