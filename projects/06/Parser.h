#include <iostream>
#include <fstream>
#include <string>
#include <vector>

const char A_COMMAND = 'A';
const char C_COMMAND = 'C';
const char L_COMMAND = 'L';
const char BLANK = 'B';
const char COMMENT = 'c';

using namespace std;

class Parser {
	ifstream assemblyFile;
	string currentCommand;
	string DEST, COMP, JUMP;
	
	public:
	Parser(string filename);
	
	bool hasMoreCommands();
	
	string advance(); 
	
	char commandType();
	
	string symbol (); 
	
	string dest();
	
	string comp();
	
	string jump();
	
	void setDestCompJump();
	
	void helper();
	
	void reset();
	
	~Parser();
};

/*
Constructor/initializer - Input file/stream  — Opens the input file/stream and gets ready to parse it.

hasMoreCommands — Boolean Are there more commands in thecinput?

advance — — Reads the next command from the input and makes it the current command. Should be called only if hasMoreCommands() is true. Initially there is no current command.

commandType — A_COMMAND,C_COMMAND,L_COMMAND - Returns the type of the current command: m A_COMMAND for @Xxx where Xxx is either a symbol or a decimal number, m C_COMMAND for dest=comp;jump m L_COMMAND (actually, pseudocommand) for (Xxx) where Xxx is a symbol.

symbol — string Returns the symbol or decimal Xxx of the current command @Xxx or (Xxx). Should be called only when commandType() is A_COMMAND or L_COMMAND.

dest — string Returns the dest mnemonic in the current C-command (8 possibilities). Should be called only when commandType() is C_COMMAND.

comp — string Returns the comp mnemonic in the current C-command (28 possibilities). Should be called only when commandType() is C_COMMAND.

jump — string Returns the jump mnemonic in the current C-command (8 possibilities). Should be called only when commandType() is C_COMMAND.
*/
