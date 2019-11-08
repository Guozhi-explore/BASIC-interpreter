#include "tokenizer.h"
using namespace std;
#include<assert.h>

Tokenizer::Tokenizer(string input_line)
{
    ignoreBlankFlag=false;
    this->input_line=input_line;
    this->parseInputLineToTokenList();
}

void Tokenizer::parseInputLineToTokenList ()
{
    int index=0;
    string token_string;
    bool is_new_symbol=false;
    while(index<input_line.size())
    {
        assert(index>=0);
        if(input_line[index]==' '&&ignoreBlankFlag==false)
        {
            if(is_new_symbol==true)
            {
                addNewSymbol(token_string);
                token_string="";
            }
            is_new_symbol=false;
        }else{
            token_string.push_back(input_line[index]);
            is_new_symbol=true;
        }
        index++;
    }
    addNewSymbol(token_string);
}


void Tokenizer::addNewSymbol(string token_string)
{
    assert(token_string.size()>0);
    Token token;
    token.token_string=token_string;
    assert(token_string==token.token_string);
    //judge string is number or not
    bool is_number=true;
    for(int i=0;i<token_string.size();++i)
    {
        char c=token_string[i];

        if(!isdigit(c))
        {
            is_number=false;
            break;
        }
    }
    if(is_number==true)
    {
        token.token_type=NUMBER;
        Token token1;
        token1.token_string=token_string;
        token1.token_type=NUMBER;
        this->token_list.push(token1);
        return;
    }
    //judge string is string or not
    if(token_string[0]=='\"')
    {

    }

    //judge string is ID&RESERVE or not
    int string_head=0,string_rear=0;
    for(int i=0;i<token_string.size();++i)
    {
        //may be operator
        if(!alphabetAndDigit(token_string[i]))
        {
            if(string_rear>string_head)
            {
                token.token_string=token_string.substr(string_head,string_rear-string_head);
                this->addIdOrReserve(token.token_string);
            }
            if(isOperator(token_string[i]))
            {
                token.token_type=OPERATOR;
                token.token_string=token_string[i];
                this->token_list.push(token);
                string_head=i+1;
            }
            else{
                //UNDEFINED TOKEN
                token.token_type=ERROR;
                token.token_string=token_string[i];
                this->token_list.push(token);
                string_head=i+1;
            }
        }
        string_rear++;
    }
    if(string_rear>string_head)
    {
        token.token_string=token_string.substr(string_head,string_rear-string_head);
        this->addIdOrReserve(token.token_string);
    }

}
Tokenizer::Token Tokenizer::getToken()
{
    if(this->token_list.empty()==false)
    {
        Token token=this->token_list.front();
        this->token_list.pop();
        return token;
    }
    else {
         Token token;
         return token;
    }
}

bool Tokenizer::alphabetAndDigit (char s)
{
    bool belong_flag=false;
    if(s>='a'&&s<='z')  belong_flag=true;
    if(s>='A'&&s<='Z')  belong_flag=true;
    if(isdigit(s))  belong_flag=true;
    return belong_flag;
}

bool Tokenizer::isOperator (char s)
{
    return (s=='+'||s=='-'||s=='*'||s=='/'||s=='('||s==')'||s=='=');
}

void Tokenizer::addIdOrReserve (string token_string)
{
    Token token;
    token.token_string=token_string;
    if(isReserveToken(token_string))
    {
        token.token_type=RESERVE;
    }
    else{
        token.token_type=ID;
    }
    this->token_list.push(token);
    return;
}

bool Tokenizer::isReserveToken(string token_string)
{
    return (token_string=="REM"||
    token_string=="LET"||
    token_string=="PRINT"||
    token_string=="INPUT"||
    token_string=="GOTO"||
    token_string=="IF"||
    token_string=="END"||
    token_string=="RUN"||
    token_string=="LIST"||
    token_string=="CLEAR"||
    token_string=="HELP"||
    token_string=="QUIT");
}

bool Tokenizer::hasMoreToken()
{
    return !this->token_list.empty();
}
