#ifndef IF_STATEMENT_INCLUDED
#define IF_STATEMENT_INCLUDED

#include "Statement.h"
#include "ProgramState.h"

class IfStatement: public Statement
{
private:
	string m_var;
	string m_op;
	int m_ifnum;
	int m_newline;


public:
	IfStatement(string var, string op, int ifnum, int newline);
	~IfStatement();
	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif