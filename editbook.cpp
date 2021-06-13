#include "editbook.h"
#include "ui_editbook.h"

editBook::editBook(QMap<QString, QStringList> * bookdb, const QString &isbn, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::editBook)
{
    this->isbn = isbn;
    this->bookdb = bookdb;
    ui->setupUi(this);
    ui->lineEdit_isbn->setText(isbn);
    ui->lineEdit_title->setText(bookdb->value(isbn).at(0));
    ui->lineEdit_author->setText(bookdb->value(isbn).at(1));
    ui->lineEdit_publisher->setText(bookdb->value(isbn).at(2));
    ui->lineEdit_subject->setText(bookdb->value(isbn).at(3));
    ui->lineEdit_language->setText(bookdb->value(isbn).at(4));
    ui->spinBox_numpages->setValue(bookdb->value(isbn).at(5).toInt());
    ui->spinBox_numpages->setValue(bookdb->value(isbn).at(6).toInt());
}

editBook::~editBook()
{
    delete ui;
}

void editBook::on_pushButton_save_clicked()
{
    QStringList qsl;
    qsl << ui->lineEdit_title->text() << ui->lineEdit_author->text() <<
                                       ui->lineEdit_subject->text() << ui->lineEdit_publisher->text() <<
                                       ui->lineEdit_language->text() << ui->spinBox_numpages->text() <<
                                       ui->spinBox_available->text();
    bookdb->insert(isbn, qsl);
    if (Book::saveChanges(bookdb))
        QMessageBox::information(nullptr, "Edited Successfully", isbn + " Edited Successfully\nPlease Refresh The Table");
    this->close();
    delete this;

}
