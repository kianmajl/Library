#include "edit_user_profile.h"
#include "ui_edit_user_profile.h"

Edit_User_profile::Edit_User_profile(Ui::MainWindow *uiMainWindow, QWidget *admin_dash, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Edit_User_profile)
{
    this->uiMainWindow = uiMainWindow;
    this->admin_dash = admin_dash;
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
            ui->tableWidget->setItem(j, 1, new QTableWidgetItem(i.value()[0]));
            ui->tableWidget->setItem(j, 2, new QTableWidgetItem((i.value()[1].toInt()) ? "Female" : "Male"));
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
    return User::SaveUsers(user_data);
}

Edit_User_profile::~Edit_User_profile()
{
    delete ui;
}

void Edit_User_profile::on_pushButton_backtodash_clicked()
{
    this->close();
    // Refresh Data on Admin Dashboard
    {
        QString user_admin = uiMainWindow->label_username->text().remove(0, 3);
        uiMainWindow->pushButton_totaluser->setText("Total Users : " + QString::number(user_data.size()));
        uiMainWindow->frame_2->setStyleSheet((user_data[user_admin][1].toInt()) ? "image: url(:/icons/icons/librarian.png);" : "image: url(:/icons/icons/librarian-m.png);");
    }
    admin_dash->show();
}

void Edit_User_profile::on_lineEdit_textChanged(const QString &arg1)
{
    QList<QTableWidgetItem *> qlwi = ui->tableWidget->findItems(arg1, Qt::MatchExactly);
    for (const auto &i : qlwi)
        ui->tableWidget->setCurrentItem(i);
}

void Edit_User_profile::on_tableWidget_currentCellChanged(int currentRow)
{
    QTableWidgetItem *tmp = ui->tableWidget->item(currentRow, 0);
    if (tmp) // if item exists !
        ui->lineEdit->setText(tmp->text());
}

void Edit_User_profile::on_pushButton_edit_clicked()
{
    if (!ui->tableWidget->selectedItems().size())
    {
        QMessageBox::critical(nullptr, "No Item Selected", "Please Select an Item to edit");
        return;
    }
    Edit_User_Data * eud = new Edit_User_Data(ui->tableWidget->selectedItems()[0]->text(), true);
    eud->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
    eud->show();
}

void Edit_User_profile::on_pushButton_delete_clicked()
{
    if (!ui->tableWidget->selectedItems().size())
    {
        QMessageBox::critical(nullptr, "No Item Selected", "Please Select an Item to delete");
        return;
    }
    QString user = ui->tableWidget->selectedItems()[0]->text();
    if (user_data[user][2].toInt()) // check user isAdmin
    {
        QMessageBox::critical(nullptr, "Error", "You can not delete admin users");
        return;
    }
    int ret = QMessageBox::warning(nullptr, "Confirm Delete User", "Are you sure you want to delete user : " + user + " ?", QMessageBox::Yes | QMessageBox::No);
    if (ret == QMessageBox::Yes)
        user_data.remove(user);
    saveChanges();
    LoadData();
}

void Edit_User_profile::on_pushButton_Refresh_clicked()
{
    LoadData();
}
