#include "statement.h"
#include"assert.h"
statement::statement(){}

statement::~statement(){}

LetStatement::LetStatement(CompoundExp *exp)
{
    this->compoundexp=exp;
}

void LetStatement::execute(evalstate &state, map<int,int> &nextStatementArray,int currentLine)
{
    this->execute(state);
}

void LetStatement::execute(evalstate &state)
{
    exp *leftExp,*rightExp;
    string leftName;
    int rightValue;
    leftExp=this->compoundexp->getLHS();
    assert(leftExp->type()==IDENTIFIER);
    rightExp=this->compoundexp->getRHS();
    assert(this->compoundexp->getOperator()=="=");
    rightValue=rightExp->eval(state);
    leftName=((IdentifierExp *)leftExp)->getIdentifierName();
    state.setValue(leftName,rightValue);
    return;
}

LetStatement::~LetStatement()
{
    delete compoundexp;
}

PrintStatement::PrintStatement(exp *exp)
{
    expression=exp;
}

void PrintStatement::execute(evalstate &state, map<int,int> &nextStatementArray,int currentLine)
{
    printf("%d\n",this->expression->eval(state));
}

void PrintStatement::execute(evalstate &state)
{
    printf("%d\n",this->expression->eval(state));
}
InputStatement::InputStatement(IdentifierExp *identifierExp)
{
    identifierexp=identifierExp;
}

void InputStatement::execute(evalstate &state, map<int,int> &nextStatementArray,int currentLine)
{
   this->execute(state);
}

void InputStatement::execute(evalstate &state)
{
    int value;
    printf("input a number:\t");
    cin>>value;
    state.setValue(this->identifierexp->getIdentifierName(),value);
}
GotoStatement::GotoStatement(exp *exp)
{
    this->expression=exp;
}

void GotoStatement::execute(evalstate &state, map<int,int> &nextStatementArray,int currentLine)
{
    nextStatementArray[currentLine]=this->expression->eval(state);
    return;
}

IfStatement::IfStatement(exp *left,string op,exp *right,exp *linenumber)
{
    this->left=left;
    this->op=op;
    this->right=right;
    this->lineNumber=linenumber;
}

void IfStatement::execute(evalstate &state, map<int,int> &nextStatementArray,int currentLine)
{
    int leftValue,rightValue;
    int jumpLine;
    leftValue=this->left->eval(state);
    rightValue=this->right->eval(state);
    jumpLine=this->lineNumber->eval(state);
    if((this->op=="="&&leftValue==rightValue)||
            (this->op==">"&&leftValue>rightValue)||
            (this->op=="<"&&leftValue<rightValue))
    {
        nextStatementArray[currentLine]=jumpLine;
    }
    return;
}

EndStatement::EndStatement(){}

void EndStatement::execute(evalstate &state, map<int,int> &nextStatementArray,int currentLine)
{
    //complete protocol
    nextStatementArray[currentLine]=-1;
    return;
}
