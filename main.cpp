#include "spaceship.h"
#include "widget.h"
#include "bullet.h"
#include "linksignal.h"
#include "asteroid.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}
