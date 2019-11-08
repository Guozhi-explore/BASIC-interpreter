#include "parser.h"
#include "assert.h"
#include<stack>
parser::parser()
{

}

//versio of ugly exp parser
/*
 *
exp *parser::parseExp(Tokenizer &tokenizer)
{
    int originPrecedence=0,newPrecedence=0;
    stack<string> opStack;
    stack<exp*> valueStack;
    string oldOpExp;
    exp *newValueExp,*oldValueExp1,*oldValueExp2;
    while(tokenizer.hasMoreToken())
    {
        Tokenizer::Token token;
        token=tokenizer.getToken();
        if(token.token_type==Tokenizer::OPERATOR)
        {
            newPrecedence=this->getPrecedence(token.token_string);
            if(token.token_string=="(")
            {
                opStack.push(token.token_string);
                continue;
            }
            while(newPrecedence<=originPrecedence&&opStack.empty()==false&&valueStack.empty()==false)
            {
                oldOpExp=opStack.top();
                opStack.pop();
                oldValueExp1=valueStack.top();
                if(valueStack.empty()){
                    printf("illegal expression\n");
                    return nullptr;
                }
                valueStack.pop();
                oldValueExp2=valueStack.top();
                newValueExp=new CompoundExp(oldOpExp,oldValueExp1,oldValueExp2);
                valueStack.push(newValueExp);
                if(!opStack.empty())
                    originPrecedence=this->getPrecedence(opStack.top());
            }
            if(opStack.empty()==false&&opStack.top()=="("&&token.token_string==")")
                opStack.pop();
            opStack.push(token.token_string);
        }
        else{
            if(token.token_type==Tokenizer::NUMBER)
            {
                newValueExp=new ConstantExp(atoi(token.token_string.c_str()));
                valueStack.push(newValueExp);
            }else{
                if(token.token_type==Tokenizer::ID)
                {
                    newValueExp=new IdentifierExp(token.token_string);
                    valueStack.push(newValueExp);
                }
                else{
                    printf("illegal expression\n");
                    return nullptr;
                }
            }
        }
    }
    while(!opStack.empty()&&!valueStack.empty())
    {
        oldOpExp=opStack.top();
        opStack.pop();
        oldValueExp1=valueStack.top();
        valueStack.pop();
        if(valueStack.empty()==true)
        {
            printf("illegal expression\n");
            return nullptr;
        }
        oldValueExp2=valueStack.top();
        valueStack.pop();
        newValueExp=new CompoundExp(oldOpExp,oldValueExp1,oldValueExp2);
        valueStack.push(newValueExp);
    }
    newValueExp=valueStack.top();
    valueStack.pop();
    if(opStack.empty()==false||valueStack.empty()==false)
    {
        printf("illegal expression\n");
        return nullptr;
    }
    return newValueExp;
}
*/

exp * parser::parseExp(Tokenizer &tokenizer)
{
    exp *parseResult=parseTokensByPrecedence(tokenizer,0);
    if(tokenizer.hasMoreToken())
    {
        printf("redundant words :%s",tokenizer.getToken().token_string.c_str());
    }
    return parseResult;
}

exp *parser::parseTokensByPrecedence(Tokenizer &tokenizer,int precedence)
{
    exp *leftexp=parseParenthesesScopeToken(tokenizer),*rightexp;
    Tokenizer::Token token;
    int newPrecedence;
    while(true)
    {
        token=tokenizer.getToken();
        newPrecedence=getPrecedence( token.token_string);
        if(newPrecedence<=precedence)
        {
            break;
        }
        rightexp=parseTokensByPrecedence(tokenizer,newPrecedence);
        leftexp=new CompoundExp(token.token_string,leftexp,rightexp);
    }
    tokenizer.saveToken(token);
    return leftexp;

}
exp* parser::parseParenthesesScopeToken(Tokenizer &tokenizer)
{
    exp *exp;
    Tokenizer::Token token=tokenizer.getToken();

    if(token.token_type==Tokenizer::ID)
        return new IdentifierExp(token.token_string);
    if(token.token_type==Tokenizer::NUMBER)
        return new ConstantExp(atoi(token.token_string.c_str()));
    if(token.token_string!="(")
    {
        printf("illegal expression\n");
        return nullptr;
    }
    exp=parseTokensByPrecedence(tokenizer,0);
    if(tokenizer.getToken().token_string!=")")
    {
        printf("( and ) unblanced\n");
        return nullptr;
    }
    return exp;
}

int parser::getPrecedence(string op)
{
    if(op=="*"||op=="/")
        return 3;
    if(op=="+"||op=="-")
        return 2;
    if(op=="=")
        return 1;
    return 0;
}
