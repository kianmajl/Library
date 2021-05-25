#ifndef USER_H
#define USER_H

#include <QString>
#include <QStringList>
#include <QFile>
#include <QTextStream>

class User
{
public:
    static QString Login(QString user, QString hashed_pass);
    static QString Register(QString user, QString hashed_pass, bool isAdmin = false);
    User();
    User(QString username, QString password, bool admin);
    QString getUsername();
    bool getIsAdmin();
    QString toString();

private:
    QString username;
    QString password;
    bool isAdmin;
};

#endif // USER_H
