#ifndef ADDBOOK_H
#define ADDBOOK_H

#include <QWidget>
#include <QMessageBox>
#include "book.h"
#include "editbook.h"

namespace Ui {
class addBook;
}

class addBook : public QWidget
{
    Q_OBJECT

public:
    explicit addBook(QWidget *parent = nullptr);
    ~addBook();

private slots:
    void on_pushButton_save_clicked();

private:
    Ui::addBook *ui;
    QMap<QString, QStringList> data;
};

#endif // ADDBOOK_H
