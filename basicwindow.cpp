#include "basicwindow.h"

#include"error.h"
BasicWindow::BasicWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("BASIC");
    this->setFixedSize(BASIC_WINDOW_WIDTH,BASIC_WINDOW_HEIGHT);
    console=new Console(this);
    console->setGeometry(0, 0, BASIC_WINDOW_WIDTH, BASIC_WINDOW_HEIGHT);
    this->console->write("Minimal BASIC -- Type HELP for help\n\n");
    connect(console,SIGNAL(newLineWritten(string)),this,SLOT(receiveNewLine(string)));
}

BasicWindow::~BasicWindow()
{
}

void BasicWindow::receiveNewLine(string str)
{
    //get the input value in INPUT expression if prior order is INPUT
    if(this->console->isInputValue==true){
        int value=atoi(str.c_str());
        this->console->inputEvalstate->setValue(
                    this->console->inputIdentifierExp->getIdentifierName(),
                    value);
        this->console->isInputValue=false;
        return;
    }
    //normal code line input
    try{
        this->handle(str,_program,_evalstate,*console);
    }
    // handle errors as syntax error should not lead the program to exit
    catch (ErrorException & ex) {
         if(ex.getMessage()!="") {
            console->writeErrorMsg(ex.getMessage());
         }
      }
}

void BasicWindow::handle(string input_line,program &_program, evalstate &_evalstate,Console &console)
{
    parser parser;
    Tokenizer tokenizer(input_line);
    Tokenizer::Token token;
    statement *statement;
    int lineNumber;
    token=tokenizer.getToken();

    switch (token.token_type) {
    case Tokenizer::NONE:
        break;
    case Tokenizer::ERROR:
        error("illegal token letter");
        break;
    case Tokenizer::NUMBER:
        lineNumber=atoi(token.token_string.c_str());
        if(tokenizer.hasMoreToken())
        {
            //parse tokens to _program
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
            _program.run(console);
            return;
        }else{
            if(token.token_string=="CLEAR")
            {
                _program.clear();
                return;
            }else{
                if(token.token_string=="QUIT")
                {
                    exit(0);
                }
                else{
                    if(token.token_string=="HELP")
                    {
                        console.writeHelpMsg("if you are not familiar with BASIC yet, look at\n"
                              "https://ipads.se.sjtu.edu.cn/courses/sep/proj2.pdf\n"
                              "for more information");
                        return;
                    }
                    else{
                        if(token.token_string=="LIST")
                        {
                            _program.ListSourceCode(console);
                            return;
                        }
                        else{
                            //token.token_string belong to{LET,PRINT,INPUT},which bring a statement without lineNumbee
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
                                    printstatement->execute(_evalstate,console);
                                    return;
                                }
                                if(token.token_string=="INPUT")
                                {
                                    tokenizer.saveToken(token);
                                    statement=parser.parseStatement(tokenizer);
                                    InputStatement *inputstatement=(InputStatement*) statement;
                                    inputstatement->execute(_evalstate,console);
                                    return;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
        error("error token");
        break;
    default:
        error("illegal token");
        break;
    }
    return;
}

