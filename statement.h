#ifndef STATEMENT_H
#define STATEMENT_H
#include<string>
#include "evalstate.h"
#include"exp.h"

using namespace std;

class statement
{

public:
     statement();
    virtual ~statement();
    virtual void execute(evalstate & state,map<int,int> &nextStatementArray) = 0;
};

class LetStatement: public statement {
public:
    LetStatement(CompoundExp *exp);
    virtual void execute(evalstate &state,map<int,int> &nextStatementArray);
    ~LetStatement();
private:
    CompoundExp *exp;
};

class PrintStatement: public statement {
public:
    PrintStatement(exp *expression);
    virtual void execute(evalstate &state,map<int,int> &nextStatementArray);
private:
    exp *expression;
};

class InputStatement: public statement {
public:
    InputStatement(IdentifierExp *exp);
    virtual void execute(evalstate &state,map<int,int> &nextStatementArray);
private:
    IdentifierExp *exp;
};

class GotoStatement: public statement {
public:
    GotoStatement(exp *exp);
    virtual void execute(evalstate &state,map<int,int> &nextStatementArray);
private:
    exp *expression;
};

class IfStatement: public statement {
public:
    IfStatement(exp *left,string op,exp *right ,exp *linenumber);
    virtual void execute(evalstate &state,map<int,int> &nextStatementArray);
private:
    exp *left;
    exp *right;
    string op;
    exp *lineNumber;
};

class EndStatement:public statement{
public:
    EndStatement();
    virtual void execute(evalstate &state,map<int,int> &nextStatementArray);

};

#endif // STATEMENT_H
