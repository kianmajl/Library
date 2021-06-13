#include "issuedbooks_admin.h"
#include "ui_issuedbooks_admin.h"

issuedBooks_admin::issuedBooks_admin(Ui::MainWindow *ui_admin_dash, QWidget *dash, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::issuedBooks_admin)
{
    this->change = false;
    this->admin_dash = dash;
    this->ui_admin_dash = ui_admin_dash;
    ui->setupUi(this);
    this->loadData();
}

int issuedBooks_admin::loadData()
{
    this->issuedbooksdb = book_item::loadData_issuedBooks();
    ui->tableWidget->setRowCount(0);

    // Set Completer
    {
        for (int i = 0; i < completer.size(); i++)
            delete completer.at(i);
        completer.clear();
        QStringList tmp;

        for (auto it = issuedbooksdb.constBegin(); it != issuedbooksdb.constEnd(); ++it)
            tmp << it.key().first;
        this->completer.append(new QCompleter(tmp, this));

        tmp.clear();
        for (auto it = issuedbooksdb.constBegin(); it != issuedbooksdb.constEnd(); ++it)
            tmp << it.key().second;
        tmp.removeDuplicates();
        this->completer.append(new QCompleter(tmp, this));

        tmp.clear();
        for (auto it = issuedbooksdb.constBegin(); it != issuedbooksdb.constEnd(); ++it)
            tmp << it.value().toString("dddd, MMMM dd, yyyy");
        tmp.removeDuplicates();
        this->completer.append(new QCompleter(tmp, this));

        tmp.clear();
        for (auto it = issuedbooksdb.constBegin(); it != issuedbooksdb.constEnd(); ++it)
            tmp << it.value().addDays(MAX_DAYS).toString("dddd, MMMM dd, yyyy");
        tmp.removeDuplicates();
        this->completer.append(new QCompleter(tmp, this));


        for (int i = 0; i < 4; ++i)
            completer.at(i)->setCaseSensitivity(Qt::CaseInsensitive);

    }

    // Add to table
    {
        int j = 0;
        for (auto i = issuedbooksdb.constBegin(); i != issuedbooksdb.constEnd(); ++i)
        {
            ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            ui->tableWidget->setItem(j, 0, new QTableWidgetItem(i.key().first));
            ui->tableWidget->setItem(j, 1, new QTableWidgetItem(i.key().second));
            ui->tableWidget->setItem(j, 2, new QTableWidgetItem(i.value().toString("dddd, MMMM dd, yyyy")));
            ui->tableWidget->setItem(j, 3, new QTableWidgetItem(i.value().addDays(MAX_DAYS).toString("dddd, MMMM dd, yyyy")));
            ++j;
        }
    }

    ui->label->setText("Issued Books List | " + QString::number(issuedbooksdb.size()) + " Records Loaded");
    return issuedbooksdb.size();
}

issuedBooks_admin::~issuedBooks_admin()
{
    delete ui;
}

void issuedBooks_admin::on_pushButton_refresh_clicked()
{
    this->change = true;
    this->loadData();
}

void issuedBooks_admin::on_lineEdit_search_textChanged(const QString &arg1)
{
    if (arg1 == "")
    {
        for (int i = 0; i < ui->tableWidget->rowCount(); ++i)
            ui->tableWidget->showRow(i);
        ui->label->setText("Issued Books List | " + QString::number(issuedbooksdb.size()) + " Records Loaded");
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
        else
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
        ui->label->setText("Issued Books List | " + QString::number(cnt) + " Records Loaded");
    }
}

void issuedBooks_admin::on_comboBox_search_currentIndexChanged(int index)
{
    ui->lineEdit_search->clear();
    if (index)
        ui->lineEdit_search->setCompleter(completer.at(index - 1));
    else
        ui->lineEdit_search->setCompleter(0);
}

void issuedBooks_admin::on_pushButton_backtodash_clicked()
{
    this->hide();
    if (change)
    {
        ui_admin_dash->pushButton_totalbissued->setText("Total Books Issued : " + QString::number(issuedbooksdb.size()));
        change = false;
    }
    this->admin_dash->show();

}

void issuedBooks_admin::on_pushButton_return_clicked()
{
    QMap<QString, QStringList> booksdb = book_item::loadBooks();
    if (!ui->tableWidget->selectedItems().size())
    {
        QMessageBox::critical(nullptr, "No Item Selected", "Please Select an Item to return");
        return;
    }

    QString key = ui->tableWidget->selectedItems().at(0)->text(); //ISBN
    QString user = ui->tableWidget->selectedItems().at(1)->text();
    issuedbooksdb.remove(qMakePair(key, user));
    booksdb[key][6] = QString::number(booksdb.value(key).at(6).toInt() + 1);
    book_item::saveChanges_issuedBooks(issuedbooksdb);
    book_item::saveChanges(booksdb);
    QMessageBox::information(nullptr, "Returned Successfully", "Book Returned Successfully\nDate: " + QDate::currentDate().toString("dddd, MMMM dd, yyyy"));
    loadData();
    this->change = true;
}
