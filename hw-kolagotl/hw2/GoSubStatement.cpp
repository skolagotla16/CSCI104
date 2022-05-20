//GoSubStatement.cpp
#include "GoSubStatement.h"
using namespace std;

GoSubStatement::GoSubStatement(int val)
	: val1( val )
{}

GoSubStatement::~GoSubStatement(){}

void GoSubStatement::execute(ProgramState* state, ostream &outf)
{
    state -> goSubState(val1);
}