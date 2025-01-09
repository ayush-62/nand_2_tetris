#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

const char C_ARITHMETIC = 'A';
const char C_PUSH = 'P';
const char C_POP = 'O';
const char C_LABEL = 'L';
const char C_GOTO = 'G';
const char C_IF = 'I';
const char C_FUNCTION = 'F';
const char C_RETURN = 'R';
const char C_CALL = 'C';
const char C_COMMENT = 'T';
const char C_BLANK = 'B';

using namespace std;

class Parser {
	
	ifstream vmFile;
	string currentCommand, cmd, argm1, argm2;
	char cmdType;
	
	public:
		
		Parser(string filename);
		
		bool hasMoreCommands();
		
		string advance(); 
		
		char commandType();
		
		string arg1(); 
		
		int arg2();
		
		//helper methods
		void setCmdArg1Arg2();
		
		void printStatus();
		
		void reset();

		void setFile(string file);
		
		~Parser();
};

/*
Constructor -  	Input file/stream -- Opens the input file/stream and gets ready to parse it.

hasMoreCommands -- boolean Are there more commands in the input?

advance -- --   Reads the next command from the input and makes it the current command. Should be called only if hasMoreCommands is true. 
				Initially there is no current command.

commandType --  C_ARITHMETIC, C_PUSH, C_POP, C_LABEL, C_GOTO, C_IF, C_FUNCTION, C_RETURN, C_CALL - Returns the type of the current VM command. 
				C_ARITHMETIC is returned for all the arithmetic commands.

arg1 -- string - 	Returns the first arg. of the current command. In the case of C_ARITHMETIC, the command itself (add, sub, etc.) is returned. 
				 	Should not be called if the current command is C_RETURN.

arg2 -- int - 	Returns the second argument of the current command. Should be called only if the current command is C_PUSH, C_POP, C_FUNCTION, or C_CALL.

*/

