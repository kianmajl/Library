#ifndef ADDBOOK_H
#define ADDBOOK_H

#include <QWidget>

namespace Ui {
class addBook;
}

class addBook : public QWidget
{
    Q_OBJECT

public:
    explicit addBook(QWidget *parent = nullptr);
    ~addBook();

private:
    Ui::addBook *ui;
};

#endif // ADDBOOK_H
