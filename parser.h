#ifndef PARSER_H
#define PARSER_H


#include<string>
#include<exp.h>
#include"statement.h"
#include"errno.h"

class parser
{
public:
    parser();
    statement *parseStatement(Tokenizer &tokenizer);
    exp *parseExp(Tokenizer &tokenizer);
    int getPrecedence(string op);
private:
    /*
     * return ID or NUMBEER or parentheses value
     * */
    exp* parseParenthesesScopeToken(Tokenizer &tokenizer);
    /*
     *return a compound expression whose op's precedence is bigger than prioir one
     * */
    exp* parseTokensByPrecedence(Tokenizer &tokenizer,int precedence);
};

#endif // PARSER_H
