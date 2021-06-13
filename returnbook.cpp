#include "returnbook.h"
#include "ui_returnbook.h"

returnBook::returnBook(Ui::MainWindow_user *ui_user_dash, const QString &user, QWidget *user_dash, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::returnBook)
{
    this->user = user;
    this->dash = user_dash;
    this->ui_user_dash = ui_user_dash;
    this->change = false;
    ui->setupUi(this);
    this->loadData();
}

void returnBook::mousePressEvent(QMouseEvent *event)
{
    oldPos = event->globalPosition();
}

void returnBook::mouseMoveEvent(QMouseEvent *event)
{
    const QPointF delta = event->globalPosition() - oldPos;
    move(x()+delta.x(), y()+delta.y());
    oldPos = event->globalPosition();
}

int returnBook::loadData()
{
    j = 0;
    ui->lineEdit_search->clear();
    ui->tableWidget->setRowCount(0);
    this->booksdb = Book::loadBooks();
    this->issuedbooksdb = book_item::loadData_issuedBooks();

    // Set Completer
    {
        for (int i = 0; i < completer.size(); i++)
            delete completer.at(i);
        completer.clear();
        QStringList tmp;

        for (auto it = issuedbooksdb.constBegin(); it != issuedbooksdb.constEnd(); ++it)
            if (it.key().second == user)
                tmp << it.key().first;
        this->completer.append(new QCompleter(tmp, this));

        for (int i = 0; i < 6; i++)
        {
            tmp.clear();
            for (auto it = booksdb.constBegin(); it != booksdb.constEnd(); ++it)
                if (issuedbooksdb.contains(qMakePair(it.key(), user)))
                    tmp << it.value().at(i);
            this->completer.append(new QCompleter(tmp, this));
        }

        tmp.clear();
        for (auto it = issuedbooksdb.constBegin(); it != issuedbooksdb.constEnd(); ++it)
            if(it.key().second == user)
                tmp << it.value().toString("dddd, MMMM dd, yyyy");
        this->completer.append(new QCompleter(tmp, this));

        tmp.clear();
        for (auto it = issuedbooksdb.constBegin(); it != issuedbooksdb.constEnd(); ++it)
            if (it.key().second == user)
                tmp << it.value().addDays(MAX_DAYS).toString("dddd, MMMM dd, yyyy");
        this->completer.append(new QCompleter(tmp, this));

        for (int i = 0; i < 9; ++i)
            completer.at(i)->setCaseSensitivity(Qt::CaseInsensitive);

    }

    // Add to table
    {
        QDate currentDate = QDate::currentDate();

        for (auto i = issuedbooksdb.constBegin(); i != issuedbooksdb.constEnd(); ++i)
        {
            if (i.key().second == user)
            {
                QDate expire_date = i.value().addDays(MAX_DAYS);
                qint64 d = currentDate.daysTo(expire_date);
                int k;
                ui->tableWidget->insertRow(ui->tableWidget->rowCount());

                QTableWidgetItem * isbn = new QTableWidgetItem();
                isbn->setText(i.key().first);
                ui->tableWidget->setItem(j, 0, isbn);
                if (d < 4 && d > -1)
                    isbn->setBackground(QBrush(QColor(236, 180, 91)));
                else if (d < 0)
                    isbn->setBackground(QBrush(QColor(216, 85, 49)));

                for (k = 0; k < booksdb.value(i.key().first).size() - 1; ++k)
                {
                    QTableWidgetItem * data = new QTableWidgetItem();
                    data->setText(booksdb.value(i.key().first).at(k));
                    ui->tableWidget->setItem(j, k + 1, data);
                    if (d < 4 && d > -1)
                        data->setBackground(QBrush(QColor(236, 180, 91)));
                    else if (d < 0)
                        data->setBackground(QBrush(QColor(216, 85, 49)));
                }

                QTableWidgetItem * issue_date = new QTableWidgetItem();
                issue_date->setText(i.value().toString("dddd, MMMM dd, yyyy"));
                QTableWidgetItem * ex_date = new QTableWidgetItem();
                ex_date->setText(i.value().addDays(MAX_DAYS).toString("dddd, MMMM dd, yyyy"));
                ui->tableWidget->setItem(j, ++k, issue_date);
                ui->tableWidget->setItem(j, ++k, ex_date);
                if (d < 4 && d > -1)
                {
                    issue_date->setBackground(QBrush(QColor(236, 180, 91)));
                    ex_date->setBackground(QBrush(QColor(236, 180, 91)));
                }
                else if (d < 0)
                {
                    issue_date->setBackground(QBrush(QColor(216, 85, 49)));
                    ex_date->setBackground(QBrush(QColor(216, 85, 49)));
                }
                ++j;
            }
        }
    }

    ui->label->setText("Issued Books List | " + QString::number(j) + " Records Loaded");
    return j;

}

returnBook::~returnBook()
{
    delete ui;
}

void returnBook::on_pushButton_refresh_clicked()
{
    this->loadData();
}

void returnBook::on_lineEdit_search_textChanged(const QString &arg1)
{
    if (arg1 == "")
    {
        for (int i = 0; i < ui->tableWidget->rowCount(); ++i)
            ui->tableWidget->showRow(i);
        ui->label->setText("Issued Books List | " + QString::number(j) + " Records Loaded");
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

void returnBook::on_comboBox_search_currentIndexChanged(int index)
{
    ui->lineEdit_search->clear();
    if (index)
        ui->lineEdit_search->setCompleter(completer.at(index - 1));
    else
        ui->lineEdit_search->setCompleter(0);
}

void returnBook::on_pushButton_backtodash_clicked()
{
    this->hide();
    if (change)
    {
        ui_user_dash->pushButton_totalbissued->setText("Total Books Issued : " + QString::number(book_item::numIssued(user)));
        change = false;
    }
    this->dash->show();
}

void returnBook::on_pushButton_return_clicked()
{
    if (!ui->tableWidget->selectedItems().size())
    {
        QMessageBox::critical(nullptr, "No Item Selected", "Please Select an Item to return");
        return;
    }

    QString key = ui->tableWidget->selectedItems().at(0)->text(); //ISBN
    issuedbooksdb.remove(qMakePair(key, user));
    booksdb[key][6] = QString::number(booksdb.value(key).at(6).toInt() + 1);
    book_item::saveChanges_issuedBooks(issuedbooksdb);
    book_item::saveChanges(booksdb);
    QMessageBox::information(nullptr, "Returned Successfully", "Book Returned Successfully\nDate: " + QDate::currentDate().toString("dddd, MMMM dd, yyyy"));
    loadData();
    this->change = true;
}
