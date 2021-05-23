#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <QWidget>

namespace Ui {
class authentication;
}

class authentication : public QWidget
{
    Q_OBJECT

public:
    explicit authentication(QWidget *parent = nullptr);
    ~authentication();

private:
    Ui::authentication *ui;
};

#endif // AUTHENTICATION_H
