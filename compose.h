#ifndef COMPOSE_H
#define COMPOSE_H

#include <QWidget>
#include <QCompleter>
#include <QMessageBox>
#include "user.h"
#include "message.h"

namespace Ui {
class Compose;
}

class Compose : public QWidget
{
    Q_OBJECT

public:
    explicit Compose(QWidget *dash, QString sender, QString reciver = "", QString subject = "", QString txt = "", QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    ~Compose();

private slots:
    void on_pushButton_backtodash_clicked();

    void on_pushButton_clicked();

private:
    Ui::Compose *ui;
    QWidget *dash;
    QString sender;
    QPointF oldPos; // for draggable
    QMap<QString, QStringList> users;
};

#endif // COMPOSE_H
