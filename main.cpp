#include "basicwindow.h"

#include <QApplication>
#include<iostream>
#include<fstream>
#include<string>
#include"tokenizer.h"
using namespace std;

void handle(string input_line);


int main(int argc, char *argv[])
{
   /* QApplication a(argc, argv);
    BasicWindow w;
    w.show();
    return a.exec();*/
    string str;
    while(true)
    {
        try{
            getline(std::cin,str);
        }
        catch(ifstream::failure e)
        {
            cerr<<"exception read user input\n";
        }
        handle(str);
    }
    return 0;
}

void handle(string input_line)
{
    Tokenizer tokenizer(input_line);
    Tokenizer::Token token;
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
        if(tokenizer.hasMoreToken())
        {
            //parse tokens to program

        }else{
            //empty tokens just delete
        }

        break;
    case Tokenizer::RESERVE:
    {
        if(token.token_string=="RUN")
        {

        }else{
            if(token.token_string=="CLEAR")
            {

            }else{
                if(token.token_string=="QUIT")
                {

                }
                else{
                    if(token.token_string=="HELP")
                    {

                    }
                    else{
                        if(token.token_string=="LIST")
                        {

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
