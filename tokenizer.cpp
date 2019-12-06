#include "tokenizer.h"
using namespace std;
#include<assert.h>

Tokenizer::Tokenizer(string input_line)
{
    ignoreBlankFlag=false;
    this->input_line=input_line;
    this->parseInputLineToTokenList();
}
/*
 * parse tokens use blank space
 * */
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
    if(token_string!="")
    addNewSymbol(token_string);
}


void Tokenizer::addNewSymbol(string token_string)
{
    assert(token_string.size()>0);
    Token token;
    token.token_string=token_string;


    //judge string is ID||RESERVE||NUMBER or not
    int string_head=0,string_rear=0;
    for(int i=0;i<token_string.size();++i)
    {
        //may be operator
        if(!alphabetAndDigit(token_string[i]))
        {
            if(string_rear>string_head)
            {
                token.token_string=token_string.substr(string_head,string_rear-string_head);
                this->addIdOrReserveOrNumber(token.token_string);
            }
            if(isOperator(token_string[i]))
            {
                token.token_type=OPERATOR;
                token.token_string=token_string[i];

                //to implement ** operator conveniently,replace ** with ^
                if(!this->token_list.empty())

                if(this->token_list.empty()==false&&
                        this->token_list.back().token_string=="*"&&
                        token.token_string=="*")
                {
                    token.token_string="^";
                    //delete last token which is *
                    this->token_list.erase(token_list.end()-1);
                }

                this->token_list.push_back(token);
                string_head=i+1;
            }
            else{
                //UNDEFINED TOKEN
                token.token_type=ERROR;
                token.token_string=token_string[i];
                this->token_list.push_back(token);
                string_head=i+1;
            }
        }
        string_rear++;
    }
    if(string_rear>string_head)
    {
        token.token_string=token_string.substr(string_head,string_rear-string_head);
        this->addIdOrReserveOrNumber(token.token_string);
    }

}

//getToken() func can help parse and main to select suitable parse choice
Tokenizer::Token Tokenizer::getToken()
{
    if(return_token.empty()==false)
    {
        Token token=return_token.front();
        return_token.pop();
        return token;
    }
    if(this->token_list.empty()==false)
    {
        Token token=this->token_list.front();
        this->token_list.erase(token_list.begin());
        return token;
    }
    else {
         Token token;
         return token;
    }
}

void Tokenizer::saveToken(Token token)
{
    return_token.push(token);
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
    return (s=='+'||s=='-'||s=='*'||s=='/'||s=='('||s==')'||s=='='||s=='>'||s=='<');
}

void Tokenizer::addIdOrReserveOrNumber (string token_string)
{
    Token token;
    token.token_string=token_string;

    /*judge string is number of not*/
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
        //case negative number
        //if number follows a negative operator,modify its token_string
        if(!this->token_list.empty()&&this->token_list.back().token_string=="-")
        {
            if(this->token_list[token_list.size()-2].token_type==RESERVE
                    ||(this->token_list[token_list.size()-2].token_type==OPERATOR
                     &&this->token_list[token_list.size()-2].token_string!=")")
                    ||this->token_list[token_list.size()-2].token_string=="^")
            {
                this->token_list.erase(token_list.end()-1);
                token.token_string="-"+token.token_string;
            }
        }
        this->token_list.push_back(token);
        return;
    }

    /*judge string is reserve or token*/
    if(isReserveToken(token_string))
    {
        token.token_type=RESERVE;
    }
    else{
        token.token_type=ID;
    }
    this->token_list.push_back(token);
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
    if(this->return_token.empty()==false&&this->return_token.front().token_type!=NONE)
        return true;
    return (!this->token_list.empty());
}
