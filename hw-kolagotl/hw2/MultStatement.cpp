// MultStatement.cpp:
#include "MultStatement.h"
using namespace std;

MultStatement::MultStatement(std::string name, std::string mult_value)
	: m_name( name ), m_mult_value( mult_value )
{}

MultStatement::~MultStatement(){}



void MultStatement::execute(ProgramState* state, ostream &outf)
{
    state -> multState(m_name, m_mult_value);
}