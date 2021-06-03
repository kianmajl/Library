#include "user.h"

#define USER_FILE "userdb.txt"
#define SEP_DATA ","

QString User::Login(QString user, QString hashed_pass)
{
    QFile user_data(USER_FILE);

    if (!user_data.open(QIODevice::ReadOnly | QIODevice::Text))
        return "No Users Record Found !";

    QTextStream in(&user_data);
    while (!in.atEnd())
    {
        QStringList data = in.readLine().split(SEP_DATA);
        if (data[0] == user && data[1] == hashed_pass)
        {
            user_data.close();
            if (data[2].toInt()) // Check Sex
                return (data[3].toInt()) ? "ok_admin_f" : "ok_f";
            else
                return (data[3].toInt()) ? "ok_admin_m" : "ok_m";
        }
    }

    user_data.close();
    return "Invalid Username or Password";
}

QString User::Register(QString user, QString hashed_pass, bool sex, bool isAdmin)
{
    QFile user_data(USER_FILE);

    if (!user_data.open(QIODevice::ReadWrite | QIODevice::Text))
        return "Error in opening file !";

    QTextStream out(&user_data);
    while (!out.atEnd())
    {
        QStringList data = out.readLine().split(SEP_DATA);
        if (data[2].toInt() && isAdmin) // Check for is Admin exists
        {
            user_data.close();
            return "The admin already exists !";
        }
        if (data[0] == user) // Check for duplicate username
        {
            user_data.close();
            return "This username already exists !";
        }
    }

    User new_user(user, hashed_pass, sex, isAdmin);
    out << new_user.toString();
    return "ok";
}

int User::LoadedData()
{
    int cnt = 0;
    QFile user_data(USER_FILE);

    if (!user_data.open(QIODevice::ReadOnly | QIODevice::Text))
        return 0;

    QTextStream in(&user_data);
    while (!in.atEnd())
    {
        in.readLine();
        cnt++;
    }

    user_data.close();
    return cnt;
}

QMap<QString, QStringList> User::LoadUsers()
{
    QMap<QString, QStringList> user_data;
    QFile userfile(USER_FILE);

    userfile.open(QIODevice::ReadOnly | QIODevice::Text);

    QTextStream in(&userfile);
    while (!in.atEnd())
    {
        QStringList data = in.readLine().split(SEP_DATA);
        user_data[data[0]] << data[1] << data[2] << data[3]; // key: username | values : passwors,sex,isAdmin
    }

    userfile.close();
    return user_data;
}

bool User::SaveUsers(QMap<QString, QStringList> &data)
{
    QFile userfile(USER_FILE);

    if (!userfile.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&userfile);
    for (auto it = data.constBegin(); it != data.constEnd(); ++it)
        out << it.key() << SEP_DATA << it.value().join(SEP_DATA) << "\n";
    userfile.close();
    return true;
}

User::User(QString username, QString password, bool sex, bool admin)
{
    this->username = username;
    this->password = password;
    this->sex = sex;
    this->isAdmin = admin;
}

QString User::toString()
{
    QStringList qsl;
    qsl << this->username << this->password << QString::number(this->sex) << QString::number(this->isAdmin);
    return qsl.join(SEP_DATA) + "\n";
}
