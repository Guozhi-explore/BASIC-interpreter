#include "basicwindow.h"

#include"error.h"
BasicWindow::BasicWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("BASIC");
    this->setFixedSize(BASIC_WINDOW_WIDTH,BASIC_WINDOW_HEIGHT);
    console=new Console(this);
    console->setGeometry(0, 0, BASIC_WINDOW_WIDTH, BASIC_WINDOW_HEIGHT);
    this->console->write("Minimal BASIC -- Type HELP for help\n\n");
    thread=new HandleInputLineThread();
    connect(console,SIGNAL(newLineWritten(string)),this,SLOT(receiveNewLine(string)));
    //connect(console,SIGNAL(letHandleThreadSleep()),thread,SLOT(sleep));
    //connect(console,SIGNAL(letHandleThreadRecover()),thread,SLOT())
}

BasicWindow::~BasicWindow()
{
}

void BasicWindow::receiveNewLine(string str)
{
    bool programRerun=false;
    //get the input value in INPUT expression if prior order is INPUT
    if(this->console->isInputValue==true){
        int value=atoi(str.c_str());
        this->console->inputEvalstate->setValue(
                    this->console->inputIdentifierExp->getIdentifierName(),
                    value);
        this->console->isInputValue=false;
        if(this->console->isProgramInput==false)
        {
            return;
        }
        programRerun=true;
        this->console->isProgramInput=false;
    }
    //normal code line input
    try{
        thread->handle(str,_program,_evalstate,*console,programRerun);
    }
    // handle errors as syntax error should not lead the program to exit
    catch (ErrorException & ex) {
         if(ex.getMessage()!="") {
             if(ex.getMessage()=="QUIT")
             {
                 error("QUIT");
             }
            console->writeErrorMsg(ex.getMessage());
         }
      }
}


