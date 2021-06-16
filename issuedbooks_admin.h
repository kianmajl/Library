#ifndef ISSUEDBOOKS_ADMIN_H
#define ISSUEDBOOKS_ADMIN_H

#include <QCompleter>
#include <QWidget>
#include <QMessageBox>
#include <QMouseEvent>
#include "book_item.h"
#include "ui_mainwindow.h"

namespace Ui {
class issuedBooks_admin;
}

class issuedBooks_admin : public QWidget
{
    Q_OBJECT

public:
    explicit issuedBooks_admin(Ui::MainWindow *ui_admin_dash, QWidget *dash, QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    int loadData();
    ~issuedBooks_admin();

private slots:
    void on_pushButton_refresh_clicked();

    void on_lineEdit_search_textChanged(const QString &arg1);

    void on_comboBox_search_currentIndexChanged(int index);

    void on_pushButton_backtodash_clicked();

    void on_pushButton_return_clicked();

private:
    Ui::issuedBooks_admin *ui;
    Ui::MainWindow *ui_admin_dash;
    QWidget *admin_dash;
    QMap<QPair<QString, QString>, QDate> issuedbooksdb;
    QVector<QCompleter *> completer;
    QPointF oldPos; // for draggable
    bool change;
};

#endif // ISSUEDBOOKS_ADMIN_H
