#include "booklist_admin.h"
#include "ui_booklist_admin.h"

BookList_Admin::BookList_Admin(QWidget *dash, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BookList_Admin)
{
    this->admin_dash = dash;
    ui->setupUi(this);
    this->loadData();
}

int BookList_Admin::loadData()
{
    ui->tableWidget->setRowCount(0);
    int ld = 0;
    this->booksdb = Book::loadBooks();

    // Add to table
    {
        int j = 0;
        for (auto i = booksdb.begin(); i != booksdb.end(); ++i)
        {
            ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            ui->tableWidget->setItem(j, 0, new QTableWidgetItem(i.key()));
            ui->tableWidget->setItem(j, 1, new QTableWidgetItem(i.value().at(0)));
            ui->tableWidget->setItem(j, 2, new QTableWidgetItem(i.value().at(1)));
            ui->tableWidget->setItem(j, 3, new QTableWidgetItem(i.value().at(2)));
            ui->tableWidget->setItem(j, 4, new QTableWidgetItem(i.value().at(3)));
            ui->tableWidget->setItem(j, 5, new QTableWidgetItem(i.value().at(4)));
            ui->tableWidget->setItem(j, 6, new QTableWidgetItem(i.value().at(5)));
            ui->tableWidget->setItem(j, 7, new QTableWidgetItem(i.value().at(6)));
            ++j;
        }
    }

    ld = booksdb.size();
    ui->label->setText("Books List | " + QString::number(ld) + " Records Loaded");
    return ld;
}

BookList_Admin::~BookList_Admin()
{
    delete ui;
}

void BookList_Admin::on_pushButton_backtodash_clicked()
{
    this->hide();
    admin_dash->show();
}

void BookList_Admin::on_pushButton_refresh_clicked()
{
    this->loadData();
}

void BookList_Admin::on_pushButton_add_clicked()
{
    addBook * ab = new addBook();
    ab->show();
}
