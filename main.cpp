#include "basicwindow.h"

#include <QApplication>

/*
 * QT main program
 * run a qtwidget to interact with user input
 * things have to do 12/6
 * handle user input in program
 * negative numbeer
 *
 * */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BasicWindow w;
    w.show();
    return a.exec();
}
