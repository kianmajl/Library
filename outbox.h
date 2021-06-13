#ifndef OUTBOX_H
#define OUTBOX_H

#include <QWidget>
#include <QMapIterator>
#include "message.h"

namespace Ui {
class outbox;
}

class outbox : public QWidget
{
    Q_OBJECT

public:
    explicit outbox(QWidget *dash, const QString &user, QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    int loadData();
    ~outbox();

private slots:
    void on_pushButton_clicked();

    void on_tableWidget_currentCellChanged(int currentRow);

    void on_pushButton_backtodash_clicked();

private:
    Ui::outbox *ui;
    QWidget *dash;
    QString user;
    QPointF oldPos; // for draggable
    QMap <QString, QStringList> messagedb;
};

#endif // OUTBOX_H
