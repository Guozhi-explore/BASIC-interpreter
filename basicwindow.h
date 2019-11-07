#ifndef BASICWINDOW_H
#define BASICWINDOW_H

#include <QMainWindow>
#include"Console.h"

class BasicWindow : public QMainWindow
{
    Q_OBJECT
    Console *console;

public:
    BasicWindow(QWidget *parent = nullptr);
    ~BasicWindow();
private:
    static const int BASIC_WINDOW_WIDTH = 800;
    static const int BASIC_WINDOW_HEIGHT = 600;
};
#endif // BASICWINDOW_H
