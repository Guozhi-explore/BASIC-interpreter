#ifndef BASICWINDOW_H
#define BASICWINDOW_H


#include <QMainWindow>
#include"Console.h"

#include"program.h"
#include"evalstate.h"
#include"parser.h"

using namespace std;

class BasicWindow : public QMainWindow
{
    Q_OBJECT
public:
    BasicWindow(QWidget *parent = nullptr);
    ~BasicWindow();
public slots:
    void receiveNewLine(string line);
private:
    Console *console;
    program _program;
    evalstate _evalstate;
    static const int BASIC_WINDOW_WIDTH = 800;
    static const int BASIC_WINDOW_HEIGHT = 600;
    void handle(string input_line,program &_program, evalstate &_evalstate,Console &console);
};
#endif // BASICWINDOW_H
