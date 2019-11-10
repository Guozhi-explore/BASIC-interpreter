#include "Console.h"
#include <QKeyEvent>
#include <QTextLine>
#include <QTextCursor>
#include "error.h"
Console::Console(QWidget *parent) : QTextEdit(parent)
{

}


void Console::clear()
{
    this->clear();
}


void Console::write(string msg)
{
    QString qstring;
    qstring=QString::fromStdString(msg);
    this->setTextColor( QColor(Qt::green));
    this->append(qstring);
    //this->setTextColor(QColor(Qt::green));
}

void Console::writeErrorMsg(string msg)
{
    QString qstring;
    qstring=QString::fromStdString(msg);
    this->setTextColor(QColor(Qt::red));
    this->append(qstring);
    this->setTextColor(QColor(Qt::green));
}

void Console::writePrintMsg(string msg)
{
    QString qstring;
    qstring=QString::fromStdString(msg);
    this->setTextColor(QColor(Qt::yellow));
    this->append(qstring);
    this->setTextColor(QColor(Qt::green));
}

void Console::writeHelpMsg(string msg)
{
    QString qstring;
    qstring=QString::fromStdString(msg);
    this->setTextColor(QColor(Qt::cyan));
    this->append(qstring);
    this->setTextColor(QColor(Qt::green));
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
        if(INPUTstatement==true)
        {
            inputValue=atoi(lastLine.c_str());
            INPUTstatement=false;
        }
        else{
        newLineWritten(lastLine);
        }
    }
    QTextEdit::keyPressEvent(event);
}

int Console::getInputValue(){
    if(this->INPUTstatement=true){
       this->letHandleThreadSleep();
    }
    return inputValue;
}


