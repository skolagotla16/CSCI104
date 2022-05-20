//GoToStatement.cpp
#include "GoToStatement.h"
using namespace std;

GoToStatement::GoToStatement(int val)
	: val1( val )
{}

GoToStatement::~GoToStatement(){}

void GoToStatement::execute(ProgramState* state, ostream &outf)
{
    state -> gotoState(val1); 
}