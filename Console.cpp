#include "Console.h"
#include <QKeyEvent>
#include <QTextLine>
#include <QTextCursor>

Console::Console(QWidget *parent) : QTextEdit(parent)
{

}


void Console::clear()
{
    this->clear();
}

void Console::write(QString msg)
{
    this->append(msg+'\n');
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
        newLineWritten(lastLine);
    }
    QTextEdit::keyPressEvent(event);
}
