#include "client.h"
#include "widget.h"

#include <QApplication>
#include <QFile>

QStringList parseConf()
{
    QFile config(":/cfg/config.ini");
    QStringList lines;

    if (!config.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << config.errorString();
        return lines;
    }

    QTextStream in(&config);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        lines.append(line);
    }
    qDebug() << lines;
    config.close();
    return lines;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    QStringList lines = parseConf();
    QStringList ip = lines.takeAt(0).split(":");
    QStringList port = lines.takeAt(0).split(":");
    Client c(ip[1], port[1].toInt());

    w.show();

    return a.exec();
}
