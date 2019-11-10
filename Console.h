#ifndef CONSOLE_H
#define CONSOLE_H

#include <QObject>
#include <QTextEdit>
#include <QWidget>
#include <iostream>
#include "evalstate.h"
#include"exp.h"
using namespace std;

class Console : public QTextEdit
{
    Q_OBJECT
public:
    explicit Console(QWidget *parent = nullptr);
signals:
    void newLineWritten(string newline);
    void letHandleThreadSleep();
    void letHandleThreadRecover();

public slots:
    void clear();
    void write(string msg);
    //void writeCommand(string msg);
    void writeErrorMsg(string msg);
    void writePrintMsg(string msg);
    void writeHelpMsg(string msg);
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;

public:
    evalstate *inputEvalstate;
    IdentifierExp *inputIdentifierExp;
    bool isInputValue=false;
    int getInputValue();
    bool INPUTstatement=false;
    int inputValue;
};

#endif // CONSOLE_H
