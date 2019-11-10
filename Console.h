#ifndef CONSOLE_H
#define CONSOLE_H

#include <QObject>
#include <QTextEdit>
#include <QWidget>
#include <iostream>
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
};

#endif // CONSOLE_H
