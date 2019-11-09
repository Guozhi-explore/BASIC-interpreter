#include "exp.h"
#include "assert.h"
#include<cmath>

exp::exp()
{

}

exp::~exp(){}

/********************************ConstantExp************************/

ConstantExp::ConstantExp(int val)
{
    this->value=val;
}

int ConstantExp::eval(evalstate &state){
    return value;
}

ExpressionType ConstantExp::type()
{
    return ExpressionType::CONSTANT;
}

int ConstantExp::getConstantValue()
{
    return value;
}



/***************************IdentifierExp*************************/

IdentifierExp::IdentifierExp(string name)
{
    this->name=name;
}

int IdentifierExp::eval(evalstate &state)
{
    if(!state.isDefined(name))
    {
        printf("%s is undefined",name.c_str());
        return -1;
    }
    return state.getValue(name);
}

ExpressionType IdentifierExp::type()
{
    return ExpressionType::IDENTIFIER;
}

string IdentifierExp::getIdentifierName()
{
    return name;
}


/*********************************CompoundExp*****************************/
CompoundExp::CompoundExp(string op,exp *lhs,exp *rhs)
{
    this->op=op;
    this->lhs=lhs;
    this->rhs=rhs;
}

CompoundExp::~CompoundExp()
{
    delete lhs;
    delete rhs;
}

int CompoundExp::eval(evalstate &state)
{
    int rightValue=rhs->eval(state);
    if(op=="=")
    {
        state.setValue(((IdentifierExp*)lhs)->getIdentifierName(),rightValue);
        return rightValue;
    }
    int leftValue=lhs->eval(state);
    if(op=="+") return leftValue+rightValue;
    if(op=="-") return leftValue-rightValue;
    if(op=="*") return leftValue*rightValue;
    if(op=="/"){
        if(rightValue==0)
        {
            printf("Division by 0");
            assert(rightValue!=0);
        }
        return leftValue/rightValue;
    }
    if(op=="^")
    {
        return pow(leftValue,rightValue);
    }
    printf("illegal operator in expression");
    return 0;
}

ExpressionType CompoundExp::type()
{
    return ExpressionType::COMPOUND;
}

string CompoundExp::getOperator()
{
    return op;
}

class::exp *CompoundExp::getLHS()
{
    return this->lhs;
}

class::exp *CompoundExp::getRHS()
{
    return this->rhs;
}
