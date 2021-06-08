#include "booklist_admin.h"
#include "ui_booklist_admin.h"

BookList_Admin::BookList_Admin(QWidget *dash, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BookList_Admin)
{
    this->admin_dash = dash;
    ui->setupUi(this);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->loadData();
}

void BookList_Admin::mousePressEvent(QMouseEvent *event)
{
    oldPos = event->globalPosition();
}

void BookList_Admin::mouseMoveEvent(QMouseEvent *event)
{
    const QPointF delta = event->globalPosition() - oldPos;
    move(x()+delta.x(), y()+delta.y());
    oldPos = event->globalPosition();
}

int BookList_Admin::loadData()
{
    ui->lineEdit_search->clear();
    ui->tableWidget->setRowCount(0);
    int ld = 0;
    this->booksdb = Book::loadBooks();

    // Set Completer
    {
        for (int i = 0; i < completer.size(); i++)
            delete completer.at(i);
        completer.clear();
        this->completer.append(new QCompleter(booksdb.keys(), this));
        for (int i = 0; i < 7; i++)
        {
            QStringList tmp;
            for (auto it = booksdb.constBegin(); it != booksdb.constEnd(); ++it)
                tmp << it.value().at(i);
            this->completer.append(new QCompleter(tmp, this));
            tmp.clear();
        }
        for (int i = 0; i < 8; ++i)
            completer.at(i)->setCaseSensitivity(Qt::CaseInsensitive);
        ui->lineEdit_search->setCompleter(completer.at(1));
    }

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
    ab->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
    ab->show();
}

void BookList_Admin::on_pushButton_delete_clicked()
{
    if (!ui->tableWidget->selectedItems().size())
    {
        QMessageBox::critical(nullptr, "No Item Selected", "Please Select an Item to delete");
        return;
    }

    QString key = ui->tableWidget->selectedItems().at(0)->text(); //ISBN
    int ret = QMessageBox::warning(nullptr, "Confirm Delete Book", "Are you sure you want to delete book : " + booksdb.value(key).at(0) + " ?", QMessageBox::Yes | QMessageBox::No);
    if (ret == QMessageBox::Yes)
        booksdb.remove(key);

    Book::saveChanges(booksdb);
    loadData();

}

void BookList_Admin::on_lineEdit_search_textChanged(const QString &arg1)
{
    if (arg1 == "")
    {
        for (int i = 0; i < ui->tableWidget->rowCount(); ++i)
            ui->tableWidget->showRow(i);
        ui->label->setText("Books List | " + QString::number(booksdb.size()) + " Records Loaded");
    }
    else
    {
        int cnt = 0;
        for (int i = 0; i < ui->tableWidget->rowCount(); ++i)
        {
            if (ui->tableWidget->item(i, ui->comboBox_search->currentIndex())->text().startsWith(arg1, Qt::CaseInsensitive))
            {
                cnt++;
                ui->tableWidget->showRow(i);
            }
            else
                ui->tableWidget->hideRow(i);
        }
        ui->label->setText("Books List | " + QString::number(cnt) + " Records Loaded");
    }
}

void BookList_Admin::on_comboBox_search_currentIndexChanged(int index)
{
    ui->lineEdit_search->setCompleter(completer.at(index));
}
