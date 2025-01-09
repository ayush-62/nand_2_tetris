#include "Parser.h"

using namespace std;

Parser::Parser(string filename) : vmFile(filename) { 
	cmd = argm1 = argm2 = "";
	cmdType = '0';
}
	
bool Parser::hasMoreCommands() {
	return (vmFile.peek() != EOF);
}
	
string Parser::advance() {
	getline(vmFile, currentCommand);
	setCmdArg1Arg2();
	commandType();
	return currentCommand;
}
	
char Parser::commandType() {
	if(cmd == "add" || cmd == "sub" || cmd == "neg" || cmd == "eq" || cmd == "gt" || cmd == "lt" || cmd == "and" || cmd == "or" || cmd == "not") cmdType = C_ARITHMETIC;
	else if(cmd == "push") cmdType = C_PUSH;
	else if(cmd == "pop") cmdType = C_POP;
	else if(cmd == "comment") cmdType = C_COMMENT;
	else if(cmd == "label") cmdType = C_LABEL;
	else if(cmd == "goto") cmdType = C_GOTO;
	else if(cmd == "if-goto") cmdType = C_IF;
	else if(cmd == "function") cmdType = C_FUNCTION;
	else if(cmd == "call") cmdType = C_CALL;
	else if(cmd == "return") cmdType = C_RETURN;
	if(cmd == "") cmdType = C_BLANK;
	return cmdType;
}
	

string Parser::arg1() {
	if(cmdType == C_ARITHMETIC) return cmd;
	// if(cmdType == C_PUSH || cmdType == C_POP || cmdType == C_LABEL || cmdType == C_GOTO || cmdType == C_IF) return argm1;
	return argm1;
}
	
int Parser::arg2() {
	return stoi(argm2);
}
	
void Parser::setCmdArg1Arg2() {
	string token = ""; 
	stringstream tokens(currentCommand);
	// printf("current command: %s\n", currentCommand);
	// cout << "current command: " << currentCommand << endl;	
	int i = 0; 
	string args[3] = {"", "", ""};

	// cout << "tokens ->  {";
	while (tokens >> token) {
		// cout << token << " * ";
		if(token.length() == 0) continue;
		
		if(token[0] == '/' && token[1] == '/') { 
			if(args[0].length() == 0) args[0] = "comment"; 
			break;	
		}
		
		args[i] = token;
	    i++;
	}
	// cout << " }\n";

	cmd = args[0];
	argm1 = args[1];
	argm2 = args[2];

	// cout << "tokens: [  ";
	// for(string s : args) { cout << s << " - ";}
	// cout << " ] \n";
}

void Parser::printStatus() {
	cout << "tokens -> { cmd: " << cmd << ", arg1: " << argm1 << ", arg2: " << argm2 << ", cmd type: " << cmdType << " }" << endl << endl;
}

void Parser::reset() {
	vmFile.clear();
	vmFile.seekg(0, vmFile.beg);
}	

void Parser::setFile(string file) {
	vmFile.close();
	vmFile.clear();
	vmFile.open(file);
	cout << "Parser ------------------------------------------------------------------------------------------ \ncurrent file: " << file << endl;
}

Parser::~Parser() {
	vmFile.close();
	vmFile.clear();
}

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

