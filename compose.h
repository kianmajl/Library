#ifndef COMPOSE_H
#define COMPOSE_H

#include <QWidget>

namespace Ui {
class Compose;
}

class Compose : public QWidget
{
    Q_OBJECT

public:
    explicit Compose(QWidget *dash, QString sender, QWidget *parent = nullptr);
    ~Compose();

private slots:
    void on_pushButton_backtodash_clicked();

private:
    Ui::Compose *ui;
    QWidget *dash;
    QString sender;
};

#endif // COMPOSE_H
