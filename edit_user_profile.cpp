#include "edit_user_profile.h"
#include "ui_edit_user_profile.h"

Edit_User_profile::Edit_User_profile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Edit_User_profile)
{
    ui->setupUi(this);
}

Edit_User_profile::~Edit_User_profile()
{
    delete ui;
}
