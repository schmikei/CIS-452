#include "mainwindow.h"

#include <QApplication>

/***************************************************
 * main method, starting point of qt Gui application
 * **************************************************/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
