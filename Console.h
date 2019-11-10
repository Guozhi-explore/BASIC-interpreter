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

public slots:
    void clear();
    void write(string msg);

protected:
    virtual void keyPressEvent(QKeyEvent *event) override;

public:
    evalstate *inputEvalstate;
    IdentifierExp *inputIdentifierExp;
    bool isInputValue=false;
};

#endif // CONSOLE_H
