#include "addbook.h"
#include "ui_addbook.h"

addBook::addBook(QMap<QString, QStringList> *data, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addBook)
{
    this->data = data;
    ui->setupUi(this);
}

addBook::~addBook()
{
    delete ui;
}

void addBook::on_pushButton_save_clicked()
{
    if (data->contains(ui->lineEdit_isbn->text()))
    {
        int ret = QMessageBox::warning(nullptr, "Error", "This ISBN already exists!\nDo you want to edit this book?", QMessageBox::Yes | QMessageBox::No);

        if (ret == QMessageBox::Yes)
        {
            editBook * eb = new editBook(data, ui->lineEdit_isbn->text());
            eb->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
            eb->show();
            this->close();
            delete this;
        }

        else
            ui->lineEdit_isbn->clear();

        return;
    }

    QStringList qsl;
    qsl << ui->lineEdit_title->text() << ui->lineEdit_author->text()
                                    << ui->lineEdit_subject->text() << ui->lineEdit_publisher->text()
                                    << ui->lineEdit_language->text() << ui->spinBox_numpages->text()
                                    << ui->spinBox_available->text();

    data->insert(ui->lineEdit_isbn->text(), qsl);
    if (Book::saveChanges(data))
        QMessageBox::information(nullptr, "Added Successfully", ui->lineEdit_title->text() + " was successfully added\nPlease Refresh The Table");

    this->close();
    delete this;
}
