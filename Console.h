#ifndef CONSOLE_H
#define CONSOLE_H

#include <QObject>
#include <QTextEdit>
#include <QWidget>
#include <iostream>
#include<semaphore.h>
using namespace std;

class Console : public QTextEdit
{
    Q_OBJECT
public:
    explicit Console(QWidget *parent = nullptr);
    int getInputValue();
signals:
    void newLineWritten(string newline);

public slots:
    void clear();
    void write(string msg);

protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
private:
    bool valueInputFlag=false;
    int inputValue;
    sem_t waitForInput;
};

#endif // CONSOLE_H
