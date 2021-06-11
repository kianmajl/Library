#include "returnbook.h"
#include "ui_returnbook.h"

returnBook::returnBook(Ui::MainWindow_user *ui_user_dash, QString user, QWidget *user_dash, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::returnBook)
{
    this->user = user;
    this->dash = user_dash;
    this->ui_user_dash = ui_user_dash;
    this->change = false;
    ui->setupUi(this);
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
        for (auto i = booksdb.constBegin(); i != booksdb.constEnd(); ++i)
            if (issuedbooksdb.contains(qMakePair(i.key(), user)))
                tmp << i.key();
        this->completer.append(new QCompleter(tmp, this));
        for (int i = 0; i < 6; i++)
        {
            tmp.clear();
            for (auto it = booksdb.constBegin(); it != booksdb.constEnd(); ++it)
                if (issuedbooksdb.contains(qMakePair(it.key(), user)))
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
            if (issuedbooksdb.contains(qMakePair(i.key(), user)))
            {
                ui->tableWidget->insertRow(ui->tableWidget->rowCount());
                ui->tableWidget->setItem(j, 0, new QTableWidgetItem(i.key()));
                for (int k = 0; k < i.value().size() - 1; ++k)
                    ui->tableWidget->setItem(j, k + 1, new QTableWidgetItem(i.value().at(k)));
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
