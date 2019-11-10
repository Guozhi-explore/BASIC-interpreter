#include "Console.h"
#include <QKeyEvent>
#include <QTextLine>
#include <QTextCursor>
#include "error.h"
Console::Console(QWidget *parent) : QTextEdit(parent)
{
    sem_init(&waitForInput,0,0);
}


void Console::clear()
{
    this->clear();
}

void Console::write(string msg)
{
    QString qstring;
    qstring=QString::fromStdString(msg);
    this->append(qstring);
}

void Console::keyPressEvent(QKeyEvent *event)
{
    /*play rules:
     * press enter to confirm word
     * press control to replay game
     * */
    if (event->key() == Qt::Key_Backspace)
        return;
    if (event->key() == Qt::Key_Delete)
        return;
    /* kick shift to replay buggle game*/

    if (this->textCursor().hasSelection())
        return;
    if (event->key() == Qt::Key_Return) {
        QTextCursor cursor = this->textCursor();
        cursor.movePosition(QTextCursor::End);
        cursor.select(QTextCursor::LineUnderCursor);
        string lastLine = cursor.selectedText().toStdString();
        if(valueInputFlag==true)
        {
            inputValue=atoi(lastLine.c_str());
            valueInputFlag=false;
            sem_post(&waitForInput);
        }
        else
        newLineWritten(lastLine);
    }
    QTextEdit::keyPressEvent(event);
}

int Console::getInputValue()
{
    this->valueInputFlag=true;
    //spin until user input a value,cause valueINputValue set to false
    sem_wait(&waitForInput);
    return this->inputValue;
}


