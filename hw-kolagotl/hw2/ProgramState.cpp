#include <iostream>
#include <vector>
#include <string>
#include <sstream> 
#include <fstream>
#include <cstdlib>
#include <map>
#include <stack>
#include <algorithm>

using namespace std;
#include "ProgramState.h"

ProgramState::ProgramState(int nums) 
    : m_numLines(nums) 
{}

ProgramState::~ProgramState(){}

//This function is called by the LET execute and assigns values to variable
void ProgramState::setState(string var, int val){

    //inserts a "name" into the map if it does not exist
    if (varMap.find(var) == varMap.end()){
        varMap.insert(pair<string, int> (var, val));
    }
    //change the value of the "name" if it already exists
    else {
        varMap.at(var) = val;
    }

}
//create a function that can jump around and be returned to
void ProgramState::goSubState(int val){
    //checks if the jump value is valid
    if (val < 1 || val > m_numLines){
        cout << "Illegal jump instruction" << endl;
        counter = -1;
        
    }
    else {

        track.push(counter + 1);
        counter = val - 1;
    }

}
//jumps to a given line
void ProgramState::gotoState(int val){
    //checks if the jump to line is valid
    if (val < 1 || val > m_numLines){
        cout << "Illegal jump instruction" << endl;
        counter = -1;
        
    }
    else{
        counter = val - 1;
    }
}

// returns to right after the go function
void ProgramState::returnState(){
    if (skip_return == true && track.empty()){
        skip_return = false;
        return; 
    }
    //if the stack is empty ends the program
    if (track.empty()){
        counter = -1;
    }
        
    else {
        counter = track.top() - 1;
        track.pop();
    }

    skip_return = true;
}
// add function
void ProgramState::addState(string var, string temp_var){
    int val2 = 0;
	if (isdigit(temp_var[0]) == 0){ //checks if the string is a digit
		val2 = varMap[temp_var];
	}
	else if (isdigit(temp_var[0]) == 1){ //checks if the string is a digit
		val2 = stoi(temp_var);
	}

    varMap[var] += val2;
}

void ProgramState::subState(string var, string temp_var){
    int val2 = 0;
 	if (isdigit(temp_var[0]) == 0){ //checks if the string is a digit
		val2 = varMap[temp_var];
	}
	else if (isdigit(temp_var[0]) == 1){ //checks if the string is a digit
		val2 = stoi(temp_var); 
	}
    varMap[var] -= val2;
}

void ProgramState::multState(string var, string temp_var){
  	int val2 = 0;
    if (isdigit(temp_var[0]) == 0){ //checks if the string is a digit
		val2 = varMap[temp_var];
	}
	else if (isdigit(temp_var[0]) == 1){ //checks if the string is a digit
		val2 = stoi(temp_var);
	}
    varMap[var] *= val2;
}

void ProgramState::divState(string var, string temp_var){
    int val2 = 0;
    if (isdigit(temp_var[0]) == 0){ //checks if the string is a digit
		val2 = varMap[temp_var];
	}
	else if (isdigit(temp_var[0]) == 1){ //checks if the string is a digit
		val2 = stoi(temp_var);
	}

    if (val2 == 0){ //checks if being divided by zero
        cout << "Divide by zero exception" << endl;
        return;
    }
    varMap[var] /= val2;
}

void ProgramState::printState(string var){ //prints value of a variable
    int zero = 0;
    if (varMap.find(var) == varMap.end()){
        varMap.insert(pair<string, int> (var, zero));
        cout << varMap[var] << endl;
    }

    else{
        cout << varMap[var] << endl;
    }
}

void ProgramState::printAllState(){ //prints all variables and values
    for (auto it = varMap.begin(); it != varMap.end(); it++){
        cout << it->first << " " << it->second << endl;
    }
}

// runs all possible operators
void ProgramState::ifState(string var, string op, int ifnum, int newline){
    int variable = varMap.at(var);
    if (newline < 1 || newline > m_numLines){
        cout << "Illegal jump instruction" << endl;
        counter = -1;
    }
    else if (op == "<>" && variable != ifnum){
        counter = newline - 1;
    }
    else if (op == "=" && variable == ifnum){
        counter = newline - 1;
    }
    else if (op == ">=" && variable >= ifnum){
        counter = newline - 1;
    }
    else if (op == ">" && variable > ifnum){
        counter = newline - 1;
    }
    else if (op == "<=" && variable <= ifnum){
        counter = newline - 1;
    }
    else if (op == "<" && variable < ifnum){
        counter = newline - 1;
    }
}
   

