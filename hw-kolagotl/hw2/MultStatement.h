#ifndef MULT_STATEMENT_INCLUDED
#define MULT_STATEMENT_INCLUDED

#include "Statement.h"
#include "ProgramState.h"

class MultStatement: public Statement
{
private:
	std::string m_name;
	std::string m_mult_value;


public:
	MultStatement(std::string name, std::string mult_value);
	~MultStatement();
	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif