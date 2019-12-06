#include "statement.h"
#include"assert.h"


statement::statement(){}

statement::~statement(){}

LetStatement::LetStatement(CompoundExp *exp)
{
    this->compoundexp=exp;
}

void LetStatement::execute(evalstate &state, map<int,int> &nextStatementArray,int currentLine,Console &console)
{
    this->execute(state);
}

void LetStatement::execute(evalstate &state)
{
    exp *leftExp,*rightExp;
    string leftName;
    int rightValue;
    leftExp=this->compoundexp->getLHS();
    if(leftExp->type()!=IDENTIFIER)
        error("in LET expression,left-value should be Identifier");
    rightExp=this->compoundexp->getRHS();
    if(this->compoundexp->getOperator()!="=")
        error("in LET expression,op should be =");
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

void PrintStatement::execute(evalstate &state, map<int,int> &nextStatementArray,int currentLine,Console &console)
{
    this->execute(state,console);
}

void PrintStatement::execute(evalstate &state,Console &console)
{
    int value=this->expression->eval(state);
    console.writePrintMsg(to_string(value));
    return;
}
InputStatement::InputStatement(IdentifierExp *identifierExp)
{
    identifierexp=identifierExp;
}

//in this way, run process can't input a value
void InputStatement::execute(evalstate &state, map<int,int> &nextStatementArray,int currentLine,Console &console)
{
   execute(state,console);
   console.isProgramInput=true;
   error("user input");
}

void InputStatement::execute(evalstate &state,Console &console)
{

    console.writePrintMsg(" ? ");
    console.isInputValue=true;
    console.inputEvalstate=&state;
    console.inputIdentifierExp=this->identifierexp;
    return;
}
GotoStatement::GotoStatement(exp *exp)
{
    this->expression=exp;
}

void GotoStatement::execute(evalstate &state, map<int,int> &nextStatementArray,int currentLine,Console &console)
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

void IfStatement::execute(evalstate &state, map<int,int> &nextStatementArray,int currentLine,Console &console)
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

void EndStatement::execute(evalstate &state, map<int,int> &nextStatementArray,int currentLine,Console &console)
{
    //complete protocol
    nextStatementArray[currentLine]=-1;
    return;
}
