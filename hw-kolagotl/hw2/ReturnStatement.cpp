// ReturnStatement.cpp:
#include "ReturnStatement.h"
using namespace std;

ReturnStatement::ReturnStatement(){}
ReturnStatement::~ReturnStatement(){}

void ReturnStatement::execute(ProgramState* state, ostream &outf)
{
    state -> returnState();
}