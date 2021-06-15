#include "booklist_admin.h"
#include "ui_booklist_admin.h"

BookList_Admin::BookList_Admin(Ui::MainWindow *ui_dash, QWidget *dash, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BookList_Admin)
{
    this->admin_dash = dash;
    this->ui_admindash = ui_dash;
    this->change = false;
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
    int j = 0;
    this->booksdb = Book::loadBooks();

    // Set Completer
    {
        for (int i = 0; i < completer.size(); i++)
            delete completer.at(i);
        completer.clear();
        this->completer.append(new QCompleter(booksdb.keys(), this));
        for (int i = 0; i < 6; i++)
        {
            QStringList tmp;
            for (auto it = booksdb.constBegin(); it != booksdb.constEnd(); ++it)
                tmp << it.value().at(i);
            this->completer.append(new QCompleter(tmp, this));
            tmp.clear();
        }
        for (int i = 0; i < 7; ++i)
            completer.at(i)->setCaseSensitivity(Qt::CaseInsensitive);
    }

    // Add to table
    {
        for (auto i = booksdb.constBegin(); i != booksdb.constEnd(); ++i)
        {
            ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            ui->tableWidget->setItem(j, 0, new QTableWidgetItem(i.key()));
            for (int k = 0; k < i.value().size(); ++k)
                ui->tableWidget->setItem(j, k + 1, new QTableWidgetItem(i.value().at(k)));
            ++j;
        }
    }

    ui->label->setText("Books List | " + QString::number(j) + " Records Loaded");
    return j;
}

BookList_Admin::~BookList_Admin()
{
    delete ui;
}

void BookList_Admin::on_pushButton_backtodash_clicked()
{
    this->hide();
    if (change)
    {
        this->ui_admindash->pushButton_totalb->setText("Total Books : " + QString::number(this->booksdb.size()));
        this->change = false;
    }
    admin_dash->show();
}

void BookList_Admin::on_pushButton_refresh_clicked()
{
    this->loadData();
}

void BookList_Admin::on_pushButton_add_clicked()
{
    addBook * ab = new addBook(&this->booksdb);
    ab->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
    ab->show();
    this->change = true;
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
    {
        booksdb.remove(key);
        book_item::deleteBooks(key);
        group_item::deleteBook(key);
        Book::saveChanges(&booksdb);
        loadData();
        this->change = true;
    }
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
        if (ui->comboBox_search->currentIndex())
        {
            for (int i = 0; i < ui->tableWidget->rowCount(); ++i)
            {
                if (ui->tableWidget->item(i, ui->comboBox_search->currentIndex() - 1)->text().startsWith(arg1, Qt::CaseInsensitive))
                {
                    cnt++;
                    ui->tableWidget->showRow(i);
                }
                else
                    ui->tableWidget->hideRow(i);
            }
        }
        else // for "All" :)
        {
            for (int i = 0; i < ui->tableWidget->rowCount(); ++i)
                ui->tableWidget->hideRow(i);
            QList<QTableWidgetItem *> filterd_items = ui->tableWidget->findItems(arg1, Qt::MatchStartsWith);
            QSet<int> rows;
            for (int i = 0; i < filterd_items.size(); ++i)
                rows.insert(filterd_items.at(i)->row());
            for (int r : rows)
                ui->tableWidget->showRow(r);
            cnt = rows.size();
        }
        ui->label->setText("Books List | " + QString::number(cnt) + " Records Loaded");
    }
}

void BookList_Admin::on_comboBox_search_currentIndexChanged(int index)
{
    ui->lineEdit_search->clear();
    if (index)
        ui->lineEdit_search->setCompleter(completer.at(index - 1));
    else
        ui->lineEdit_search->setCompleter(0); // for "All"
}

void BookList_Admin::on_pushButton_edit_clicked()
{
    if (!ui->tableWidget->selectedItems().size())
    {
        QMessageBox::critical(nullptr, "No Item Selected", "Please Select an Item to edit");
        return;
    }

    QString key = ui->tableWidget->selectedItems().at(0)->text(); //ISBN
    editBook * eb = new editBook(&this->booksdb, key);
    eb->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
    eb->show();
}
