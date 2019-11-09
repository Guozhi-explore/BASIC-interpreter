#include "basicwindow.h"

BasicWindow::BasicWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("Basic");
    this->setFixedSize(BASIC_WINDOW_WIDTH,BASIC_WINDOW_HEIGHT);
    console=new Console(this);
    console->setGeometry(0, 0, BASIC_WINDOW_WIDTH, BASIC_WINDOW_HEIGHT);
    this->console->write("welcom to basic intepreter");
    connect(console,SIGNAL(newLineWritten(string)),this,SLOT(receiveNewLine(string)));
}

BasicWindow::~BasicWindow()
{
}

void BasicWindow::receiveNewLine(string str)
{
    this->handle(str,_program,_evalstate);
}

void BasicWindow::handle(string input_line,program &_program, evalstate &_evalstate)
{
    parser parser;
    Tokenizer tokenizer(input_line);
    Tokenizer::Token token;
    statement *statement;
    int lineNumber;
    /*while(true)
    {
        token=tokenizer.getToken();
        if(token.token_type==Tokenizer::NONE)
            break;
        printf("%s,  %d\n",token.token_string.c_str(),token.token_type);
    }*/
    token=tokenizer.getToken();
    switch (token.token_type) {
    case Tokenizer::NONE:
        break;
    case Tokenizer::ERROR:
        printf("illegal token letter");
        break;
    case Tokenizer::NUMBER:
        lineNumber=atoi(token.token_string.c_str());
        if(tokenizer.hasMoreToken())
        {
            //parse tokens to _program
            //parser.parseExp(tokenizer);
            _program.addOrUpdateSourceCodeLine(lineNumber,input_line);
            statement=parser.parseStatement(tokenizer);
            _program.addOrUpdateParsedStatement(lineNumber,statement);
        }else{
            //empty tokens just delete the code line if existed in _program
            if(_program.hasLineNumberInSourceCode(lineNumber))
                _program.deleteLine(lineNumber);
        }
        break;
    case Tokenizer::RESERVE:
    {
        if(token.token_string=="RUN")
        {
            _program.run();
        }else{
            if(token.token_string=="CLEAR")
            {
                _program.clear();
            }else{
                if(token.token_string=="QUIT")
                {
                    exit(0);
                }
                else{
                    if(token.token_string=="HELP")
                    {

                    }
                    else{
                        if(token.token_string=="LIST")
                        {
                            _program.ListSourceCode();
                        }else{
                            if(token.token_string =="GOTO"||
                                    token.token_string=="IF"||
                                    token.token_string=="REM"||
                                    token.token_string=="END")
                            {
                                printf("error token\n");
                            }
                            else{
                                //token.token_string belong to{LET,PRINT,INPUT}
                                //parse rest tokens
                                {

                                    if(token.token_string=="LET")
                                    {
                                        tokenizer.saveToken(token);
                                        statement=parser.parseStatement(tokenizer);
                                        LetStatement *letstatement=(LetStatement*) statement;
                                        letstatement->execute(_evalstate);
                                        return;
                                    }
                                    if(token.token_string=="PRINT")
                                    {
                                        tokenizer.saveToken(token);
                                        statement=parser.parseStatement(tokenizer);
                                        PrintStatement *printstatement=(PrintStatement*)statement;
                                        printstatement->execute(_evalstate);
                                        return;
                                    }
                                    if(token.token_string=="INPUT")
                                    {
                                        tokenizer.saveToken(token);
                                        statement=parser.parseStatement(tokenizer);
                                        InputStatement *inputstatement=(InputStatement*) statement;
                                        inputstatement->execute(_evalstate);
                                        return;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
        break;
    default:
        printf("illegal token\n");
        break;
    }
    return;
}

