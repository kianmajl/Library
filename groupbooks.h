#ifndef GROUPBOOKS_H
#define GROUPBOOKS_H

#include <QWidget>
#include <QMouseEvent>
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
    explicit groupBooks(QWidget *admin_dash, QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    int LoadData();
    ~groupBooks();

private slots:
    void on_lineEdit_textChanged(const QString &arg1);

    void on_listWidget_currentTextChanged(const QString &currentText);

    void on_pushButton_backtodash_clicked();

private:
    Ui::groupBooks *ui;
    QWidget *admin_dash; // pointer of admin dashboard
    QPointF oldPos; // for draggable
    QStringList data; // saving data from file
};

#endif // GROUPBOOKS_H