#ifndef STATEMENT_H
#define STATEMENT_H
#include<string>
#include<iostream>
#include "evalstate.h"
#include"exp.h"
#include"error.h"
#include"Console.h"
using namespace std;

class statement
{

public:
     statement();
    virtual ~statement();
    /*
     * state to store variable's value
     * nextStatementArray to store next jump line information
     * currentline is nextStatementArray 's index
     * console to print of receive user input in the console
     * */
    virtual void execute(evalstate & state,map<int,int> &nextStatementArray,int currentLine,Console &console) = 0;
};

class LetStatement: public statement {
public:
    LetStatement(CompoundExp *exp);
    void execute(evalstate &state);
    virtual void execute(evalstate &state,map<int,int> &nextStatementArray,int currentLine,Console &console);
    ~LetStatement();
private:
    CompoundExp *compoundexp;
};

class PrintStatement: public statement {
public:
    PrintStatement(exp *expression);
    void execute(evalstate &state,Console &console);
    virtual void execute(evalstate &state,map<int,int> &nextStatementArray,int currentLine,Console &console);
private:
    exp *expression;
};

class InputStatement: public statement {
public:
    InputStatement(IdentifierExp *exp);
    void execute(evalstate &state,Console &console);
    virtual void execute(evalstate &state,map<int,int> &nextStatementArray,int currentLine,Console &console);
private:
    IdentifierExp *identifierexp;
};

class GotoStatement: public statement {
public:
    GotoStatement(exp *exp);
    virtual void execute(evalstate &state,map<int,int> &nextStatementArray,int currentLine,Console &console);
private:
    exp *expression;
};

class IfStatement: public statement {
public:
    IfStatement(exp *left,string op,exp *right ,exp *linenumber);
    virtual void execute(evalstate &state,map<int,int> &nextStatementArray,int currentLine,Console &console);
private:
    exp *left;
    exp *right;
    string op;
    exp *lineNumber;
};

class EndStatement:public statement{
public:
    EndStatement();
    virtual void execute(evalstate &state,map<int,int> &nextStatementArray,int currentLine,Console &console);

};

#endif // STATEMENT_H
