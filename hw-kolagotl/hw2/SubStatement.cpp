// SubStatement.cpp:
#include "SubStatement.h"
using namespace std;

SubStatement::SubStatement(std::string name, std::string sub_value)
	: m_name( name ), m_sub_value( sub_value )
{}

SubStatement::~SubStatement(){}



void SubStatement::execute(ProgramState* state, ostream &outf)
{
    state -> subState(m_name, m_sub_value);
}