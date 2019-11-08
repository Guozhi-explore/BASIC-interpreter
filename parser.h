#ifndef PARSER_H
#define PARSER_H


#include<string>
#include<exp.h>
#include"statement.h"

class parser
{
public:
    parser();
    exp *parseExp(Tokenizer &tokenizer);
    int getPrecedence(string op);
private:
    exp* parseParenthesesScopeToken(Tokenizer &tokenizer);
    exp* parseTokensByPrecedence(Tokenizer &tokenizer,int precedence);
};

#endif // PARSER_H
