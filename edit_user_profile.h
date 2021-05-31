#ifndef EDIT_USER_PROFILE_H
#define EDIT_USER_PROFILE_H

#include <QWidget>

namespace Ui {
class Edit_User_profile;
}

class Edit_User_profile : public QWidget
{
    Q_OBJECT

public:
    explicit Edit_User_profile(QWidget *parent = nullptr);
    ~Edit_User_profile();

private:
    Ui::Edit_User_profile *ui;
};

#endif // EDIT_USER_PROFILE_H
