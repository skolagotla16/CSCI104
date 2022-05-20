#ifndef DIV_STATEMENT_INCLUDED
#define DIV_STATEMENT_INCLUDED

#include "Statement.h"
#include "ProgramState.h"

class DivStatement: public Statement
{
private:
	std::string m_name;
	std::string m_div_value;


public:
	DivStatement(std::string name, std::string div_value);
	~DivStatement();
	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif