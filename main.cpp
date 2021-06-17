// Github Repository : https://github.com/kianmajl/Library
// by: Kian Majlessi

#include "authentication.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    authentication auth;

    auth.setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
    auth.show();

    return a.exec();
}
