#include "basicwindow.h"
#include<exception>
#include <QApplication>

/*
 * QT main program
 * run a qtwidget to interact with user input
 *
 * */

int main(int argc, char *argv[])
{
    int ret;
    try{
    QApplication a(argc, argv);
    BasicWindow w;
    w.show();
        ret=a.exec();
    }
    catch (ErrorException & ) {}
    return ret;
}
