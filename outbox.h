#ifndef OUTBOX_H
#define OUTBOX_H

#include <QWidget>

namespace Ui {
class outbox;
}

class outbox : public QWidget
{
    Q_OBJECT

public:
    explicit outbox(QWidget *parent = nullptr);
    ~outbox();

private:
    Ui::outbox *ui;
};

#endif // OUTBOX_H
