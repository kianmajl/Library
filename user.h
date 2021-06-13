#ifndef USER_H
#define USER_H

#include <QString>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QMap>

class User
{
public:
    static QString Login(const QString &user, const QString &hashed_pass);
    static QString Register(const QString &user, const QString &hashed_pass, const bool &sex, bool isAdmin = false);
    static int LoadedData();
    static QMap<QString, QStringList> LoadUsers();
    static bool SaveUsers(QMap<QString, QStringList> &data);
    User(const QString &username, const QString &password, const bool &sex, const bool &admin);
    QString toString();

private:
    QString username;
    QString password;
    bool isAdmin;
    bool sex; // 0 : male | 1 : female
};

#endif // USER_H
