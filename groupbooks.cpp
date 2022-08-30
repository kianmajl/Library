#include "groupbooks.h"
#include "ui_groupbooks.h"

#define GROUP_FILE "groupdb.txt"

groupBooks::groupBooks(QWidget *dash, bool isAdmin, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::groupBooks)
{
    this->dash = dash;
    ui->setupUi(this);

    if (!isAdmin)
    {
        ui->pushButton_add->hide();
        ui->pushButton_delete->hide();
        ui->pushButton_edit->hide();
    }

    this->LoadData();
}

void groupBooks::mousePressEvent(QMouseEvent *event)
{
    oldPos = event->globalPosition();
}

void groupBooks::mouseMoveEvent(QMouseEvent *event)
{
    const QPointF delta = event->globalPosition() - oldPos;
    move(x()+delta.x(), y()+delta.y());
    oldPos = event->globalPosition();
}

int groupBooks::LoadData()
{
    books = Book::loadBooks();
    this->groups = group_item::loadData();
    ui->treeWidget->clear();
    ui->lineEdit->clear();
    ui->treeWidget->setHeaderLabel("Groups");

    for (auto it = groups.constBegin(); it != groups.constEnd(); ++it)
    {
        QTreeWidgetItem * group_name = new QTreeWidgetItem(ui->treeWidget);
        group_name->setText(0, it.key());
        for (int i = 0; i < it.value().size(); ++i)
        {
            QTreeWidgetItem * book_name = new QTreeWidgetItem();
            book_name->setFlags(Qt::ItemIsSelectable);
            book_name->setText(0, books.value(it.value().at(i)).at(0));
            {
                QTreeWidgetItem * isbn = new QTreeWidgetItem();
                isbn->setText(0, "ISBN: " + it.value().at(i));
                book_name->addChild(isbn);
                QTreeWidgetItem * author = new QTreeWidgetItem();
                author->setText(0, "Author: " + books.value(it.value().at(i)).at(1));
                book_name->addChild(author);
                QTreeWidgetItem * publisher = new QTreeWidgetItem();
                publisher->setText(0, "Publisher: " + books.value(it.value().at(i)).at(3));
                book_name->addChild(publisher);
                QTreeWidgetItem * lang = new QTreeWidgetItem();
                lang->setText(0, "Language: " + books.value(it.value().at(i)).at(4));
                book_name->addChild(lang);
                QTreeWidgetItem * nump = new QTreeWidgetItem();
                nump->setText(0, "Number of Pages: " + books.value(it.value().at(i)).at(5));
                book_name->addChild(nump);
                QTreeWidgetItem * available = new QTreeWidgetItem();
                available->setText(0, "Number of Available: " + books.value(it.value().at(i)).at(6));
                book_name->addChild(available);
            }

            for (int i = 0; i < book_name->childCount(); ++i)
                book_name->child(i)->setFlags(Qt::ItemIsSelectable);

            group_name->addChild(book_name);
        }

        ui->treeWidget->addTopLevelItem(group_name);
    }

    QCompleter *completer = new QCompleter(groups.keys(), this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->lineEdit->setCompleter(completer);

    ui->label->setText("Group Books List | " + QString::number(groups.size()) + " Records Loaded");
    return groups.size();
}

groupBooks::~groupBooks()
{
    delete ui;
}

void groupBooks::on_pushButton_backtodash_clicked()
{
    this->close();
    dash->show();
}

void groupBooks::on_pushButton_add_clicked()
{
    addGroup * ag = new addGroup(&this->groups, &this->books);
    ag->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
    ag->show();
}

void groupBooks::on_pushButton_refresh_clicked()
{
    this->LoadData();
}

void groupBooks::on_lineEdit_textChanged(const QString &arg1)
{
    if (arg1 == "")
        ui->treeWidget->clearSelection();

    else
    {
        QList<QTreeWidgetItem *> items = ui->treeWidget->findItems(arg1, Qt::MatchStartsWith);

        for (int i = 0; i < items.size(); ++i)
            ui->treeWidget->setCurrentItem(items.at(i));
    }
}

void groupBooks::on_pushButton_edit_clicked()
{
    if (!ui->treeWidget->selectedItems().size())
    {
        QMessageBox::critical(nullptr, "No Item Selected", "Please select an item to edit");
        return;
    }

    editGroup * eg = new editGroup(&this->groups, ui->treeWidget->selectedItems().at(0)->text(0));
    eg->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
    eg->show();
}

void groupBooks::on_pushButton_delete_clicked()
{
    if (!ui->treeWidget->selectedItems().size())
    {
        QMessageBox::critical(nullptr, "No Item Selected", "Please select an item to delete");
        return;
    }

    QString key = ui->treeWidget->selectedItems().at(0)->text(0); //group_title
    int ret = QMessageBox::warning(nullptr, "Confirm Delete Group", "Are you sure you want to delete group <" + key + ">?", QMessageBox::Yes | QMessageBox::No);
    if (ret == QMessageBox::Yes)
    {
        this->groups.remove(key);
        group_item::saveChanges(&groups);
        LoadData();
    }
}
