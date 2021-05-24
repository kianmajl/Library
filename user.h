#ifndef USER_H
#define USER_H

#include <QString>


class User
{
public:
    User();
    QString getUsername();

private:
    QString username;
    QString password;
};

#endif // USER_H
