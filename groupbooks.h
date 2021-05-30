#ifndef GROUPBOOKS_H
#define GROUPBOOKS_H

#include <QWidget>
#include <QFile>
#include <QTextStream>
#include <QCompleter>

namespace Ui {
class groupBooks;
}

class groupBooks : public QWidget
{
    Q_OBJECT

public:
    explicit groupBooks(QWidget *parent = nullptr);
    void LoadData();
    ~groupBooks();

private:
    Ui::groupBooks *ui;
    QStringList data; // for saving data from file
};

#endif // GROUPBOOKS_H
