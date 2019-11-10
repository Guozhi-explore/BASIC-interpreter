#ifndef EXP_H
#define EXP_H

#include<string>

#include "tokenizer.h"
#include "evalstate.h"
enum ExpressionType{CONSTANT,IDENTIFIER,COMPOUND};


class exp
{
public:
    exp();
    virtual ~exp();
    virtual int eval(evalstate &state)=0;
   // virtual string toString()=0;
    virtual ExpressionType type()=0;

};

class ConstantExp: public exp{
public:
    ConstantExp(int val);

    virtual int eval(evalstate &state);
    //virtual string toString();
    virtual ExpressionType type();
    virtual int getConstantValue();

private:
    int value;
};

class IdentifierExp:public exp{
public:
    IdentifierExp(string name);

    virtual int eval(evalstate &state);
    //virtual string toString();
    virtual ExpressionType type();
    string getIdentifierName();

private:
    string name;

};

class CompoundExp:public exp{
public:
    CompoundExp(string op,exp *lhs,exp *rhs);
    virtual ~CompoundExp();

    virtual int eval(evalstate &state);
   // virtual string toString();
    virtual ExpressionType type();
    string getOperator();
    exp *getLHS();
    exp *getRHS();
private:
    string op;
    exp *lhs,*rhs;
};

#endif // EXP_H
