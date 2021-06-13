#ifndef EDITBOOK_H
#define EDITBOOK_H

#include <QMap>
#include <QWidget>
#include <QMessageBox>
#include "book.h"

namespace Ui {
class editBook;
}

class editBook : public QWidget
{
    Q_OBJECT

public:
    explicit editBook(QMap<QString, QStringList> * bookdb, const QString &isbn, QWidget *parent = nullptr);
    ~editBook();

private slots:
    void on_pushButton_save_clicked();

private:
    Ui::editBook *ui;
    QString isbn;
    QMap<QString, QStringList> *bookdb;
};

#endif // EDITBOOK_H
