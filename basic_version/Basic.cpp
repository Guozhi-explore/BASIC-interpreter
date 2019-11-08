#include<iostream>
#include<fstream>
#include<string>
#include "tokenizer.h"
using namespace std;
void handle(string input_line);


int main()
{
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
    while(true)
    {
        token=tokenizer.getToken();
        if(token.token_type==Tokenizer::NONE)
            break;
        printf("%s,  %d\n",token.token_type,token.token_string);
    }
}