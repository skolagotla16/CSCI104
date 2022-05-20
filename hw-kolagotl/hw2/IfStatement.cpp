//IfStatement.cpp
#include "IfStatement.h"
using namespace std;

IfStatement::IfStatement(string var, string op, int ifnum, int newline)
	: m_var( var ), m_op( op ), m_ifnum ( ifnum ), m_newline( newline )
{}

IfStatement::~IfStatement(){}

void IfStatement::execute(ProgramState* state, ostream &outf)
{
    state -> ifState(m_var, m_op, m_ifnum, m_newline); 
}