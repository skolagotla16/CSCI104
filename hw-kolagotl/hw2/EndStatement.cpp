#include "EndStatement.h"
using namespace std;

EndStatement::EndStatement(){}
EndStatement::~EndStatement(){}
void EndStatement::execute(ProgramState* state, ostream &outf)
{
	state -> counter = -1;	
}