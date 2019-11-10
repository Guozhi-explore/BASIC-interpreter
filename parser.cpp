#include "parser.h"
#include "assert.h"
#include<stack>
#include"error.h"

parser::parser()
{

}

statement *parser::parseStatement(Tokenizer &tokenizer)
{
    statement *parseStatementResult;
    Tokenizer::Token token;
    token=tokenizer.getToken();
    if(token.token_string=="LET")
    {
        exp *expression;
        expression=parseExp(tokenizer);
        if(expression->type()!=COMPOUND)
        {
            error("LET expression miss token");
        }
        parseStatementResult=new LetStatement((CompoundExp*) expression);
        return parseStatementResult;
    }
    if(token.token_string=="IF")
    {
        exp *leftExp,*rightExp,*lineExp;
        string op;
        leftExp=parseTokensByPrecedence(tokenizer,0);
        //to kinds of condition: a=b or a<b a+b<c a>1
        // the first kind can be parsed by parseTokenByPrecedence at a time
        //however the second kind have to be parsed twice
        if(leftExp->type()==COMPOUND)
        {
            CompoundExp *leftCompoundExp=(CompoundExp *)leftExp;
            //first kind
            if(leftCompoundExp->getOperator()=="=")
            {
                if(tokenizer.getToken().token_string=="THEN")
                {
                    lineExp=parseExp(tokenizer);
                    return new IfStatement(leftCompoundExp->getLHS(),leftCompoundExp->getOperator()
                                           ,leftCompoundExp->getRHS(),lineExp);
                }
                else{
                    error("miss then in IF expression");
                    return nullptr;
                }
            }
        }
        //second kind
        op=tokenizer.getToken().token_string;
        rightExp=parseTokensByPrecedence(tokenizer,0);
        if(tokenizer.getToken().token_string=="THEN")
        {
            lineExp=parseExp(tokenizer);
            return new IfStatement(leftExp,op,rightExp,lineExp);
        }
        error("miss then in IF expression");
        return nullptr;
    }
    if(token.token_string=="PRINT")
    {
        parseStatementResult=new PrintStatement(parseExp(tokenizer));
        return parseStatementResult;
    }
    if(token.token_string=="INPUT")
    {
        exp *expression;
        expression=parseExp(tokenizer);
        if(expression->type()!=IDENTIFIER)
            error("INPUT expression left-value should be identifier");
        parseStatementResult=new InputStatement((IdentifierExp*)expression);
        return parseStatementResult;
    }
    if(token.token_string=="GOTO")
    {
        parseStatementResult=new GotoStatement(parseExp(tokenizer));
        return parseStatementResult;
    }
    if(token.token_string=="END")
    {
        parseStatementResult=new EndStatement();
        return parseStatementResult;
    }
    if(token.token_string=="REM")
        return nullptr;
    error("syntax error");
    return nullptr;
}

exp * parser::parseExp(Tokenizer &tokenizer)
{
    exp *parseResult=parseTokensByPrecedence(tokenizer,0);
    if(tokenizer.hasMoreToken())
    {
        error("redundant words : "+tokenizer.getToken().token_string);
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
        // ^ is right combined
        if(newPrecedence<=precedence&&token.token_string!="^")
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
    if(token.token_type==Tokenizer::NONE)
        error("miss token");
    if(token.token_type==Tokenizer::ID)
        return new IdentifierExp(token.token_string);
    if(token.token_type==Tokenizer::NUMBER)
        return new ConstantExp(atoi(token.token_string.c_str()));
    if(token.token_string!="(")
    {
        error("illegal expression");
        return nullptr;
    }
    exp=parseTokensByPrecedence(tokenizer,0);
    if(tokenizer.getToken().token_string!=")")
    {
        error("expected )");
        return nullptr;
    }
    return exp;
}

int parser::getPrecedence(string op)
{
    if(op=="^")
        return 4;
    if(op=="*"||op=="/")
        return 3;
    if(op=="+"||op=="-")
        return 2;
    if(op=="=")
        return 1;
    return 0;
}
