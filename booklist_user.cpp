#include "booklist_user.h"
#include "ui_booklist_user.h"

booklist_user::booklist_user(const QString &user, Ui::MainWindow_user *ui_user_dash, QWidget *dash, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::booklist_user)
{
    this->user_dash = dash;
    this->change = false;
    this->user = user;
    this->ui_user_dash = ui_user_dash;
    ui->setupUi(this);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->loadData();
}

void booklist_user::mousePressEvent(QMouseEvent *event)
{
    oldPos = event->globalPosition();
}

void booklist_user::mouseMoveEvent(QMouseEvent *event)
{
    const QPointF delta = event->globalPosition() - oldPos;
    move(x()+delta.x(), y()+delta.y());
    oldPos = event->globalPosition();
}

int booklist_user::loadData()
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
        for (auto i = booksdb.constBegin(); i != booksdb.constEnd(); ++i)
            if (i.value().at(6).toInt() && !issuedbooksdb.contains(qMakePair(i.key(), user)))
                tmp << i.key();
        this->completer.append(new QCompleter(tmp, this));
        for (int i = 0; i < 6; i++)
        {
            tmp.clear();
            for (auto it = booksdb.constBegin(); it != booksdb.constEnd(); ++it)
                if (it.value().at(6).toInt() && !issuedbooksdb.contains(qMakePair(it.key(), user)))
                    tmp << it.value().at(i);
            this->completer.append(new QCompleter(tmp, this));
        }
        for (int i = 0; i < 7; ++i)
            completer.at(i)->setCaseSensitivity(Qt::CaseInsensitive);
    }

    // Add to table
    {
        for (auto i = booksdb.constBegin(); i != booksdb.constEnd(); ++i)
        {
            if (i.value().at(6).toInt() && !issuedbooksdb.contains(qMakePair(i.key(), user)))
            {
                ui->tableWidget->insertRow(ui->tableWidget->rowCount());
                ui->tableWidget->setItem(j, 0, new QTableWidgetItem(i.key()));
                for (int k = 0; k < i.value().size() - 1; ++k)
                    ui->tableWidget->setItem(j, k + 1, new QTableWidgetItem(i.value().at(k)));
                ++j;
            }
        }
    }

    ui->label->setText("Books List | " + QString::number(j) + " Records Loaded");
    return j;
}

booklist_user::~booklist_user()
{
    delete ui;
}

void booklist_user::on_lineEdit_search_textChanged(const QString &arg1)
{
    if (arg1 == "")
    {
        for (int i = 0; i < ui->tableWidget->rowCount(); ++i)
            ui->tableWidget->showRow(i);
        ui->label->setText("Books List | " + QString::number(j) + " Records Loaded");
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
        ui->label->setText("Books List | " + QString::number(cnt) + " Records Loaded");
    }
}

void booklist_user::on_comboBox_search_currentIndexChanged(int index)
{
    ui->lineEdit_search->clear();
    if (index)
        ui->lineEdit_search->setCompleter(completer.at(index - 1));
    else
        ui->lineEdit_search->setCompleter(0);
}

void booklist_user::on_pushButton_backtodash_clicked()
{
    this->hide();
    if (change)
    {
        ui_user_dash->pushButton_totalbissued->setText("Total Books Issued: " + QString::number(book_item::numIssued(user)));
        this->change = false;
    }
    user_dash->show();
}

void booklist_user::on_pushButton_issue_clicked()
{
    if (!ui->tableWidget->selectedItems().size())
    {
        QMessageBox::critical(nullptr, "No Item Selected", "Please select an item to issue");
        return;
    }

    QString key = ui->tableWidget->selectedItems().at(0)->text(); //ISBN
    issuedbooksdb.insert(qMakePair(key, user), QDate::currentDate());
    booksdb[key][6] = QString::number(booksdb.value(key).at(6).toInt() - 1);
    book_item::saveChanges_issuedBooks(issuedbooksdb);
    if(book_item::saveChanges(&booksdb))
        QMessageBox::information(nullptr, "Issued Successfully", "Book Issued Successfully\nIssue Date: " + QDate::currentDate().toString("dddd, MMMM dd, yyyy") + "\nExpiry Date: " + QDate::currentDate().addDays(MAX_DAYS).toString("dddd, MMMM dd, yyyy"));
    loadData();
    this->change = true;
    on_pushButton_backtodash_clicked();
}

void booklist_user::on_pushButton_refresh_clicked()
{
    this->loadData();
}
