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
    int LoadData();
    ~groupBooks();

private slots:
    void on_lineEdit_textChanged(const QString &arg1);

    void on_listWidget_currentTextChanged(const QString &currentText);

private:
    Ui::groupBooks *ui;
    QStringList data; // for saving data from file
};

#endif // GROUPBOOKS_H
