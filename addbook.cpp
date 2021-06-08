#include "addbook.h"
#include "ui_addbook.h"

addBook::addBook(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addBook)
{
    this->data = Book::loadBooks();
    ui->setupUi(this);
}

addBook::~addBook()
{
    delete ui;
}

void addBook::on_pushButton_save_clicked()
{
    if (data.contains(ui->lineEdit_isbn->text()))
    {
        QMessageBox::warning(nullptr, "Error", "This ISBN Already Exists");
        ui->lineEdit_isbn->clear();
        return;
    }

    data[ui->lineEdit_isbn->text()] << ui->lineEdit_title->text() << ui->lineEdit_author->text() <<
                                       ui->lineEdit_subject->text() << ui->lineEdit_publisher->text() <<
                                       ui->lineEdit_language->text() << ui->spinBox_numpages->text() <<
                                       ui->spinBox_available->text();
    if (Book::saveChanges(data))
        QMessageBox::information(nullptr, "Added Successfully", ui->lineEdit_title->text() + " Added Successfully");
    this->close();
    delete this;
}
