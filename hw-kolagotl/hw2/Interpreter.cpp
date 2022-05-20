#include "Statement.h"
#include "LetStatement.h"
#include "ProgramState.h"
#include "EndStatement.h"
#include "AddStatement.h"
#include "SubStatement.h"
#include "MultStatement.h"
#include "DivStatement.h"
#include "PrintStatement.h"
#include "PrintAllStatement.h"
#include "IfStatement.h"
#include "GoSubStatement.h"
#include "GoToStatement.h"
#include "ReturnStatement.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <vector>
#include <string>
#include <sstream> 
#include <fstream>
#include <cstdlib>
#include <map>
#include <stack>
using namespace std;


// parseProgram() takes a filename as a parameter, opens and reads the
// contents of the file, and returns an vector of pointers to Statement.
void parseProgram(istream& inf, vector<Statement *> & program);

// parseLine() takes a line from the input file and returns a Statement
// pointer of the appropriate type.  This will be a handy method to call
// within your parseProgram() method.
Statement * parseLine(string line);

// interpretProgram() reads a program from the given input stream
// and interprets it, writing any output to the given output stream.
// Note:  you are required to implement this function!
void interpretProgram(istream& inf, ostream& outf);


int main()
{
        cout << "Enter BASIC program file name: ";
        string filename;
        getline(cin, filename);
        ifstream infile(filename.c_str());
        if (!infile)
        {
                cout << "Cannot open " << filename << "!" << endl;
                return 1;
        }
        interpretProgram(infile, cout);
}



void parseProgram(istream &inf, vector<Statement *> & program)
{
	program.push_back(NULL);
	
	string line;
	while( ! inf.eof() )
	{
		getline(inf, line);
		program.push_back( parseLine( line ) );
	}
}


Statement * parseLine(string line)
{
	//these variable help read in the different parts of each line
	Statement * statement;	
	stringstream ss;
	int line_num;
	string type;
	string var;
	string op; 
	string temp_var;
	int ifnum;  
	int newline;
	int val = 0;

	ss << line; //takes whole line into the stream
	ss >> std::skipws >> line_num;
	ss >> std::skipws >> type; 
	
	//recognizes that the file calls on LET
	if ( type == "LET" )
	{
		ss >> std::skipws >> var; //up until second whitespace and adds it to var
		ss >> std::skipws >> val;
		// Note:  Because the project spec states that we can assume the file
		//	  contains a syntactically legal program, we know that
		//	  any line that begins with "LET" will be followed by a space
		//	  and then a variable and then an integer value.
		statement = new LetStatement(var, val);
	}

	//recognizes that the file calls on PRINT
	else if (type == "PRINT"){
		ss >> std::skipws >> var;
		statement = new PrintStatement(var);
	}
	//recognizes that the file calls on PRINTALL
	else if (type == "PRINTALL"){
		ss >> std::skipws >> var;
		statement = new PrintAllStatement();
	}
	//recognizes that the file calls on END or .
	else if (type == "END" || type == "."){
		statement = new EndStatement();
	}
	//recognizes that the file calls on ADD
	else if ( type == "ADD"){
		ss >> std::skipws >> var;
		ss >> std::skipws >>temp_var;
		statement = new AddStatement(var, temp_var);
			
	}
	//recognizes that the file calls on SUB
	else if ( type == "SUB"){
		ss >> std::skipws >> var;
		ss >> std::skipws >> temp_var;
		statement = new SubStatement(var, temp_var);
	}
	//recognizes that the file calls on MULT
	else if (type == "MULT"){
		ss >> std::skipws >> var;
		ss >> std::skipws >> temp_var;
		statement = new MultStatement(var, temp_var);
	}
	//recognizes that the file calls on LET DIV
	else if (type == "DIV"){
		ss >> std::skipws >> var;
		ss >> std::skipws >> temp_var;
		statement = new DivStatement(var, temp_var);
	}
	//recognizes that the file calls on IF
	else if (type == "IF"){
		ss >> std::skipws >> var;
		ss >> std::skipws >> op;
		ss >> std::skipws >> ifnum;
		ss >> std::skipws >> temp_var;
		ss >> std::skipws >> newline;
		statement = new IfStatement(var, op, ifnum, newline);
	}
	//recognizes that the file calls on GOSUB
	else if (type == "GOSUB"){
		ss >> std::skipws >> val;
		statement = new GoSubStatement(val);
	}
	//recognizes that the file calls on GOTO
	else if (type == "GOTO"){
		ss >> std::skipws >> val;
		statement = new GoToStatement(val);
	}
	//recognizes that the file calls on RETURN
	else if (type == "RETURN"){
		statement = new ReturnStatement();
	}

	return statement;
}


//void interpretProgram(istream& inf, ostream& outf);
void interpretProgram(istream& inf, ostream& outf)
{
	//cout << "Interpret Start" << endl;
	vector<Statement *> program;
	parseProgram( inf, program );
	//cout << "Parseprogram finsihed" << endl;
	Statement* t_statement = NULL;
	

	ProgramState* state = new ProgramState(program.size());
	//this for loop iterates through the program vector and executes the commans
	for(long unsigned int i = 1; i <= program.size(); i++){ 

		t_statement = program[i]; 
		state->counter = i;
		t_statement -> execute(state, outf);
		i = state -> counter;
		//breaks the loop and ends the program
		if (state -> counter == -1){
			break;
		}
	}
	//deallocates memory
	for (int j = 0; j < int(program.size()); j++){
		delete program[j];
	}
	delete state;

}
