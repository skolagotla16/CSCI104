// AddStatement.cpp:
#include "AddStatement.h"
using namespace std;

AddStatement::AddStatement(std::string name, std::string add_value)
	: m_name( name ), m_add_value( add_value )
{}

AddStatement::~AddStatement(){}


void AddStatement::execute(ProgramState* state, ostream &outf)
{
	//ProgramState tempState = *state;
    state -> addState(m_name, m_add_value);
}
