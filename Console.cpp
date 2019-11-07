#include "Console.h"
#include <QKeyEvent>
#include <QTextLine>
#include <QTextCursor>

Console::Console(QWidget *parent) : QTextEdit(parent)
{

}




void Console::write(QString msg)
{
    this->append(msg);
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

    QTextEdit::keyPressEvent(event);
}
