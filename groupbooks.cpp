#include "groupbooks.h"
#include "ui_groupbooks.h"

#define GROUP_FILE "groupdb.txt"

groupBooks::groupBooks(QWidget *dash, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::groupBooks)
{
    this->dash = dash;
    ui->setupUi(this);
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
    QMap<QString, QStringList> books = Book::loadBooks();
    this->groups = group_item::loadData();
    ui->treeWidget->clear();
    ui->treeWidget->setHeaderLabel("Groups");

    for (auto it = groups.constBegin(); it != groups.constEnd(); ++it)
    {
        QTreeWidgetItem * group_name = new QTreeWidgetItem(ui->treeWidget);
        group_name->setText(0, it.key());
        for (int i = 0; i < it.value().size(); ++i)
        {
            QTreeWidgetItem * book_name = new QTreeWidgetItem();
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
            group_name->addChild(book_name);
        }
        ui->treeWidget->addTopLevelItem(group_name);
    }

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
    addGroup * ag = new addGroup();
    ag->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
    ag->show();
}

void groupBooks::on_pushButton_refresh_clicked()
{
    this->LoadData();
}

void groupBooks::on_lineEdit_textChanged(const QString &arg1)
{
    QList<QTreeWidgetItem *> items = ui->treeWidget->findItems(arg1, Qt::MatchStartsWith);

    for (int i = 0; i < items.size(); ++i)
    {
        items.at(i)->setBackground(0, QBrush(QColor(255, 0, 0)));
    }
}
