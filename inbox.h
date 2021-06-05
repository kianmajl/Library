#ifndef INBOX_H
#define INBOX_H

#include <QWidget>
#include <QString>
#include <QStringList>
#include <QMap>
#include <QDateTime>
#include "message.h"

namespace Ui {
class inbox;
}

class inbox : public QWidget
{
    Q_OBJECT

public:
    explicit inbox(QString user, QWidget *dash, QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    int LoadData();
    ~inbox();

private slots:
    void on_pushButton_backtodash_clicked();

    void on_tableWidget_currentCellChanged(int currentRow);

private:
    Ui::inbox *ui;
    QWidget *dash;
    QPointF oldPos; // for draggable
    QMap<QString, QStringList> messages_data;
};

#endif // INBOX_H
