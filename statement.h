#ifndef STATEMENT_H
#define STATEMENT_H
#include<string>
#include "evalstate.h"
#include"program.h"
#include"exp.h"
class statement
{
public:
    virtual ~statement();
    virtual void execute(evalstate & state,program &program) = 0;
};

class LetStatement: public statement {
public:
    LetStatement(CompoundExp *exp);
    void execute(evalstate &state,program &program);
    ~LetStatement();
private:
    CompoundExp *exp;
};

class PrintStatement: public statement {
public:
    PrintStatement(exp *expression);
    void execute(evalstate &state,program &program);
private:
    exp *expression;
};

class InputStatement: public statement {
public:
    InputStatement(IdentifierExp *exp);
    void execute(evalstate &state,program &program);
private:
    IdentifierExp *exp;
};

class GotoStatement: public statement {
public:
    GotoStatement(exp *exp);
    void execute(evalstate &state,program &program);
private:
    exp *expression;
};

class IfStatement: public statement {
public:
    IfStatement(CompoundExp *exp);
    void execute(evalstate &state,program &program);
private:
    exp *left;
    exp *right;
    string op;
    exp *lineNumber;
};

class EndStatement:public statement{
public:
    EndStatement();
    void execute(evalstate &state,program &program);

};

#endif // STATEMENT_H
