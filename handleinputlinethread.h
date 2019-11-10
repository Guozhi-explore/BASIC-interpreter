#ifndef HANDLEINPUTLINETHREAD_H
#define HANDLEINPUTLINETHREAD_H
#include<QThread>
#include<string>
#include"Console.h"
#include"program.h"
#include"evalstate.h"
#include"parser.h"
using namespace std;

class HandleInputLineThread:public QThread
{
    Q_OBJECT
public:
    HandleInputLineThread();
    void handle(string input_line,program &_program, evalstate &_evalstate,Console &console);
private:

public slots:
};


#endif // HANDLEINPUTLINETHREAD_H
