// DivStatement.cpp:
#include "DivStatement.h"
using namespace std;

DivStatement::DivStatement(std::string name, std::string div_value)
	: m_name( name ), m_div_value( div_value )
{}

DivStatement::~DivStatement(){}



void DivStatement::execute(ProgramState* state, ostream &outf)
{
    state -> divState(m_name, m_div_value);
}