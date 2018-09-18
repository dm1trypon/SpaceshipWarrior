#include "const.h"
#include "client.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w("localhost", 8080);
    Client c("localhost", 8080);
    w.show();

    return a.exec();
}
