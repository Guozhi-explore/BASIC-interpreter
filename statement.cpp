#include "statement.h"

statement::statement(){}

statement::~statement(){}

LetStatement::LetStatement(CompoundExp *exp)
{
    this->exp=exp;
}

void LetStatement::execute(evalstate &state,program &program)
{
    return;
}

LetStatement::~LetStatement()
{

}

PrintStatement::PrintStatement(exp *exp)
{
    expression=exp;
}

void PrintStatement::execute(evalstate &state, program &program)
{
    return;
}

InputStatement::InputStatement(IdentifierExp *identifierExp)
{
    exp=identifierExp;
}

void InputStatement::execute(evalstate &state, program &program)
{
    return;
}

GotoStatement::GotoStatement(exp *exp)
{
    this->expression=exp;
}

void GotoStatement::execute(evalstate &state, program &program)
{
    return;
}

IfStatement::IfStatement(exp *left,string op,exp *right,exp *liennumber)
{
    this->left=left;
    this->op=op;
    this->right=right;
    this->lineNumber=lineNumber;
}

void IfStatement::execute(evalstate &state, program &program)
{
    return;
}

EndStatement::EndStatement(){}

void EndStatement::execute(evalstate &state, program &program)
{
    return;
}
