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
            return (data[2].toInt()) ? "ok_admin" : "ok";
        }
    }

    user_data.close();
    return "Invalid Username or Password";
}

QString User::Register(QString user, QString hashed_pass, bool isAdmin)
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

    User new_user(user, hashed_pass, isAdmin);
    out << new_user.toString();
    return "ok";
}

User::User(QString username, QString password, bool admin)
{
    this->username = username;
    this->password = password;
    this->isAdmin = admin;
}

QString User::getUsername()
{
    return this->username;
}

QString User::toString()
{
    QStringList qsl;
    qsl << this->username << this->password << QString::number(this->isAdmin);
    return qsl.join(SEP_DATA) + "\n";
}
