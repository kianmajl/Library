#include "edit_user_profile.h"
#include "ui_edit_user_profile.h"

Edit_User_profile::Edit_User_profile(Ui::MainWindow *uiMainWindow, QWidget *admin_dash, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Edit_User_profile)
{
    this->uiMainWindow = uiMainWindow;
    this->admin_dash = admin_dash;
    this->change = false;
    ui->setupUi(this);
    this->LoadData();
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void Edit_User_profile::mousePressEvent(QMouseEvent *event)
{
    oldPos = event->globalPosition();
}

void Edit_User_profile::mouseMoveEvent(QMouseEvent *event)
{
    const QPointF delta = event->globalPosition() - oldPos;
    move(x()+delta.x(), y()+delta.y());
    oldPos = event->globalPosition();
}

int Edit_User_profile::LoadData()
{
    ui->lineEdit->clear();
    ui->tableWidget->setRowCount(0);
    int ld = 0;
    this->user_data = User::LoadUsers();

    // Add to table
    {
        int j = 0;
        for (auto i = user_data.begin(); i != user_data.end(); ++i)
        {
            ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            ui->tableWidget->setItem(j, 0, new QTableWidgetItem(i.key()));
            ui->tableWidget->setItem(j, 1, new QTableWidgetItem(i.value().at(0)));
            ui->tableWidget->setItem(j, 2, new QTableWidgetItem((i.value().at(1).toInt()) ? "Female" : "Male"));
            ++j;
        }
    }

    QCompleter *completer = new QCompleter(user_data.keys(), this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->lineEdit->setCompleter(completer);
    ld = user_data.size();
    ui->label->setText("Users List | " + QString::number(ld) + " Records Loaded");
    return ld;
}

bool Edit_User_profile::saveChanges()
{
    return User::SaveUsers(&user_data);
}

Edit_User_profile::~Edit_User_profile()
{
    delete ui;
}

void Edit_User_profile::on_pushButton_backtodash_clicked()
{
    this->close();
    if (this->change) // Refresh Data on Admin Dashboard
    {
        this->user_data = User::LoadUsers();
        QString user_admin = uiMainWindow->label_username->text().remove(0, 3);
        uiMainWindow->pushButton_totaluser->setText("Total Users: " + QString::number(user_data.size()));
        uiMainWindow->frame_2->setStyleSheet((user_data[user_admin].at(1).toInt()) ? "image: url(:/icons/icons/librarian.png);" : "image: url(:/icons/icons/librarian-m.png);");
        this->change = false;
    }
    admin_dash->show();
}

void Edit_User_profile::on_lineEdit_textChanged(const QString &arg1)
{
    if (arg1 == "")
    {
        for (int i = 0; i < ui->tableWidget->rowCount(); ++i)
            ui->tableWidget->showRow(i);
        ui->label->setText("Users List | " + QString::number(user_data.size()) + " Records Loaded");
    }
    else
    {
        int cnt = 0;
        for (int i = 0; i < ui->tableWidget->rowCount(); ++i)
        {
            if (ui->tableWidget->item(i, 0)->text().startsWith(arg1, Qt::CaseInsensitive))
            {
                cnt++;
                ui->tableWidget->showRow(i);
            }
            else
                ui->tableWidget->hideRow(i);
        }
        ui->label->setText("Users List | " + QString::number(cnt) + " Records Loaded");
    }
}

void Edit_User_profile::on_pushButton_edit_clicked()
{
    if (!ui->tableWidget->selectedItems().size())
    {
        QMessageBox::critical(nullptr, "No Item Selected", "Please select an item to edit");
        return;
    }
    this->change = true;
    Edit_User_Data *eud = new Edit_User_Data(&this->user_data,ui->tableWidget->selectedItems().at(0)->text(), true);
    eud->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
    eud->show();
}

void Edit_User_profile::on_pushButton_delete_clicked()
{
    if (!ui->tableWidget->selectedItems().size())
    {
        QMessageBox::critical(nullptr, "No Item Selected", "Please select an item to delete");
        return;
    }
    QString user = ui->tableWidget->selectedItems().at(0)->text();
    if (user_data[user].at(2).toInt()) // check user isAdmin
    {
        QMessageBox::critical(nullptr, "Error", "You can not delete admin users!");
        return;
    }
    int ret = QMessageBox::warning(nullptr, "Confirm Delete User", "Are you sure you want to delete user <" + user + ">?", QMessageBox::Yes | QMessageBox::No);
    if (ret == QMessageBox::Yes)
    {
        user_data.remove(user);
        Message::deleteMessages(user);
        book_item::deleteUsers(user);
        this->change = true;
        saveChanges();
        LoadData();
    }
}

void Edit_User_profile::on_pushButton_Refresh_clicked()
{
    LoadData();
}
