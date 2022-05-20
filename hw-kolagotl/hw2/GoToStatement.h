#ifndef GOTO_STATEMENT_INCLUDED
#define GOTO_STATEMENT_INCLUDED

#include "Statement.h"
#include "ProgramState.h"

class GoToStatement: public Statement
{
private:
	int val1;


public:
	GoToStatement(int val1);
	~GoToStatement();
	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif