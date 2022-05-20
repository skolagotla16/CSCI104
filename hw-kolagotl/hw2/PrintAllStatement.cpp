// PrintAllStatement.cpp:
#include "PrintAllStatement.h"

PrintAllStatement::PrintAllStatement(){}
PrintAllStatement::~PrintAllStatement(){}

void PrintAllStatement::execute(ProgramState * state, std::ostream &outf)
{
  state -> printAllState();
}