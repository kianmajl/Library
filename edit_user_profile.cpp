#include "edit_user_profile.h"
#include "ui_edit_user_profile.h"

#define USER_FILE "userdb.txt"
#define SEP_DATA ","

Edit_User_profile::Edit_User_profile(QWidget *admin_dash, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Edit_User_profile)
{
    this->admin_dash = admin_dash;
    ui->setupUi(this);
    int num_loaded_data = this->LoadData();
    ui->label->setText("Users List | " + QString::number(num_loaded_data) + " Records Loaded");
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
    QFile userfile(USER_FILE);

    if (!userfile.open(QIODevice::ReadOnly | QIODevice::Text))
        return 0;

    QTextStream in(&userfile);
    while (!in.atEnd())
    {
        QStringList data = in.readLine().split(SEP_DATA);
        user_data[data[0]] << data[1] << data[2] << data[3];
    }

    userfile.close();
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
    return user_data.size();
}

bool Edit_User_profile::saveChanges()
{
    QFile userfile(USER_FILE);

    if (!userfile.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&userfile);
    for (auto it = user_data.constBegin(); it != user_data.constEnd(); ++it)
        out << it.key() << SEP_DATA << it.value().join(SEP_DATA);
    return true;
}

Edit_User_profile::~Edit_User_profile()
{
    delete ui;
}

void Edit_User_profile::on_pushButton_backtodash_clicked()
{
    this->close();
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
    ui->lineEdit->setText(tmp->text());
}

void Edit_User_profile::on_pushButton_edit_clicked()
{
    Edit_User_Data * eud = new Edit_User_Data(ui->tableWidget->selectedItems()[0]->text(), user_data);
    eud->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
    eud->show();
}
