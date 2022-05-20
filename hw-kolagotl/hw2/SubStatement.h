#ifndef SUB_STATEMENT_INCLUDED
#define SUB_STATEMENT_INCLUDED

#include "Statement.h"
#include "ProgramState.h"

class SubStatement: public Statement
{
private:
	std::string m_name;
	std::string m_sub_value;


public:
	SubStatement(std::string name, std::string sub_value);
	~SubStatement();
	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif