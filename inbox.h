#ifndef INBOX_H
#define INBOX_H

#include <QWidget>
#include <QString>
#include <QStringList>
#include <QMap>
#include <QDateTime>
#include <QMessageBox>
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
    bool saveChanges();
    ~inbox();

private slots:
    void on_pushButton_backtodash_clicked();

    void on_tableWidget_currentCellChanged(int currentRow);

    void on_pushButton_delete_clicked();

    void on_pushButton_asread_clicked();

private:
    Ui::inbox *ui;
    QWidget *dash;
    QPointF oldPos; // for draggable
    QString user;
    QMap<QString, QStringList> messages_data;
};

#endif // INBOX_H
