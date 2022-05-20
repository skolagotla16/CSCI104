all: Interpreter

Interpreter: Statement.h DivStatement.o MultStatement.o SubStatement.o AddStatement.o PrintAllStatement.o PrintStatement.o ProgramState.o LetStatement.o GoToStatement.o IfStatement.o GoSubStatement.o ReturnStatement.o EndStatement.o Interpreter.cpp
	g++ -Wall -g DivStatement.o MultStatement.o SubStatement.o AddStatement.o PrintAllStatement.o PrintStatement.o ProgramState.o LetStatement.o GoToStatement.o IfStatement.o GoSubStatement.o ReturnStatement.o EndStatement.o Interpreter.cpp -o interpreter

ProgramState.o: ProgramState.cpp ProgramState.h
	g++ -Wall -g -c ProgramState.cpp -o ProgramState.o

LetStatement.o: LetStatement.cpp LetStatement.h
	g++ -Wall -g -c LetStatement.cpp -o LetStatement.o

PrintStatement.o: PrintStatement.cpp PrintStatement.h
	g++ -Wall -g -c PrintStatement.cpp -o PrintStatement.o

PrintAllStatement.o: PrintAllStatement.cpp PrintAllStatement.h
	g++ -Wall -g -c PrintAllStatement.cpp -o PrintAllStatement.o

AddStatement.o: AddStatement.cpp AddStatement.h
	g++ -Wall -g -c AddStatement.cpp -o AddStatement.o

SubStatement.o: SubStatement.cpp SubStatement.h
	g++ -Wall -g -c SubStatement.cpp -o SubStatement.o

MultStatement.o: MultStatement.cpp MultStatement.h
	g++ -Wall -g -c MultStatement.cpp -o MultStatement.o

DivStatement.o: DivStatement.cpp DivStatement.h
	g++ -Wall -g -c DivStatement.cpp -o DivStatement.o

GoToStatement.o: GoToStatement.cpp GoToStatement.h
	g++ -Wall -g -c GoToStatement.cpp -o GoToStatement.o

IfStatement.o: IfStatement.cpp IfStatement.h
	g++ -Wall -g -c IfStatement.cpp -o IfStatement.o

GoSubStatement.o: GoSubStatement.cpp GoSubStatement.h
	g++ -Wall -g -c GoSubStatement.cpp -o GoSubStatement.o

ReturnStatement.o: ReturnStatement.cpp ReturnStatement.h
	g++ -Wall -g -c ReturnStatement.cpp -o ReturnStatement.o

EndStatement.o: EndStatement.cpp EndStatement.h
	g++ -Wall -g -c EndStatement.cpp -o EndStatement.o

.PHONY: clean
clean:
	rm -rf *.o
