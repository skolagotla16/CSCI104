#ifndef ADD_STATEMENT_INCLUDED
#define ADD_STATEMENT_INCLUDED

#include "Statement.h"
#include "ProgramState.h"

class AddStatement: public Statement
{
private:
	std::string m_name;
	std::string m_add_value;


public:
	AddStatement(std::string name, std::string add_value);
	~AddStatement();
	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif
