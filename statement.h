#ifndef STATEMENT_H
#define STATEMENT_H
#include<string>
#include<iostream>
#include "evalstate.h"
#include"exp.h"

using namespace std;

class statement
{

public:
     statement();
    virtual ~statement();
    virtual void execute(evalstate & state,map<int,int> &nextStatementArray,int currentLine) = 0;
};

class LetStatement: public statement {
public:
    LetStatement(CompoundExp *exp);
    void execute(evalstate &state);
    virtual void execute(evalstate &state,map<int,int> &nextStatementArray,int currentLine);
    ~LetStatement();
private:
    CompoundExp *compoundexp;
};

class PrintStatement: public statement {
public:
    PrintStatement(exp *expression);
    void execute(evalstate &state);
    virtual void execute(evalstate &state,map<int,int> &nextStatementArray,int currentLine);
private:
    exp *expression;
};

class InputStatement: public statement {
public:
    InputStatement(IdentifierExp *exp);
    void execute(evalstate &state);
    virtual void execute(evalstate &state,map<int,int> &nextStatementArray,int currentLine);
private:
    IdentifierExp *identifierexp;
};

class GotoStatement: public statement {
public:
    GotoStatement(exp *exp);
    virtual void execute(evalstate &state,map<int,int> &nextStatementArray,int currentLine);
private:
    exp *expression;
};

class IfStatement: public statement {
public:
    IfStatement(exp *left,string op,exp *right ,exp *linenumber);
    virtual void execute(evalstate &state,map<int,int> &nextStatementArray,int currentLine);
private:
    exp *left;
    exp *right;
    string op;
    exp *lineNumber;
};

class EndStatement:public statement{
public:
    EndStatement();
    virtual void execute(evalstate &state,map<int,int> &nextStatementArray,int currentLine);

};

#endif // STATEMENT_H
