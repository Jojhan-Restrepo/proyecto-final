#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    int interval = 60; // Default interval
    if (argc > 1) {
        bool ok;
        int tempInterval = QString(argv[1]).toInt(&ok);
        if (ok && tempInterval > 0) {
            interval = tempInterval;
        } else {
            qDebug() << "Invalid interval provided, using default interval of 60 ms.";
        }
    }

    MainWindow w(interval);
    w.show();
    return a.exec();
}
