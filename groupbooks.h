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
    explicit groupBooks(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    int LoadData();
    ~groupBooks();

private slots:
    void on_lineEdit_textChanged(const QString &arg1);

    void on_listWidget_currentTextChanged(const QString &currentText);

private:
    Ui::groupBooks *ui;
    QPointF oldPos;
    QStringList data; // for saving data from file
};

#endif // GROUPBOOKS_H
