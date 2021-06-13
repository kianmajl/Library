#ifndef GROUPBOOKS_H
#define GROUPBOOKS_H

#include <QWidget>
#include <QMouseEvent>
#include <QFile>
#include <QTextStream>
#include <QCompleter>
#include "addgroup.h"
#include "book.h"

namespace Ui {
class groupBooks;
}

class groupBooks : public QWidget
{
    Q_OBJECT

public:
    explicit groupBooks(QWidget *dash, QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    int LoadData();
    ~groupBooks();

private slots:
    void on_pushButton_backtodash_clicked();

    void on_pushButton_add_clicked();

    void on_pushButton_refresh_clicked();

private:
    Ui::groupBooks *ui;
    QWidget *dash; // pointer of dashboard
    QPointF oldPos; // for draggable
    QMap<QString, QStringList> groups;
};

#endif // GROUPBOOKS_H
