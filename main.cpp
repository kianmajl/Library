#include "authentication.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    authentication auth;

    auth.show();

    return a.exec();
}
