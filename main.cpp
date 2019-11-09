#include "basicwindow.h"

#include <QApplication>
#include<iostream>
#include<fstream>
#include<string>
#include"tokenizer.h"
#include"parser.h"
#include"program.h"
#include"evalstate.h"
using namespace std;

void handle(string input_line,program &program, evalstate &evalstate);


int main(int argc, char *argv[])
{
   /* QApplication a(argc, argv);
    BasicWindow w;
    w.show();
    return a.exec();*/
    string str;
    program program;
    evalstate evalstate;
    while(true)
    {
        try{
            getline(std::cin,str);
        }
        catch(ifstream::failure e)
        {
            cerr<<"exception read user input\n";
        }
        handle(str,program,evalstate);
    }
}

void handle(string input_line,program &program, evalstate &evalstate)
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
            //parse tokens to program
            //parser.parseExp(tokenizer);
            program.addOrUpdateSourceCodeLine(lineNumber,input_line);
            statement=parser.parseStatement(tokenizer);
            program.addOrUpdateParsedStatement(lineNumber,statement);
        }else{
            //empty tokens just delete
        }
        break;
    case Tokenizer::RESERVE:
    {
        if(token.token_string=="RUN")
        {
            program.run();
        }else{
            if(token.token_string=="CLEAR")
            {
                program.clear();
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
                            program.ListSourceCode();
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
