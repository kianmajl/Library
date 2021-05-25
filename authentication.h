#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <QWidget>
#include <QString>
#include <QCryptographicHash>
#include <QMessageBox>

namespace Ui {
class authentication;
}

class authentication : public QWidget
{
    Q_OBJECT

public:
    explicit authentication(QWidget *parent = nullptr);
    ~authentication();

private slots:
    void on_pushButton_signin_clicked();

    void on_pushButton_signup_clicked();

private:
    Ui::authentication *ui;
};

#endif // AUTHENTICATION_H
