#include "basicwindow.h"

BasicWindow::BasicWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("Basic");
    this->setFixedSize(BASIC_WINDOW_WIDTH,BASIC_WINDOW_HEIGHT);
    console=new Console(this);
    console->setGeometry(0, 0, BASIC_WINDOW_WIDTH, BASIC_WINDOW_HEIGHT);
    this->console->write("welcom to basic intepreter");
}

BasicWindow::~BasicWindow()
{
}

