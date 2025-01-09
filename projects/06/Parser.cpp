#include "Parser.h"

using namespace std;

	Parser :: Parser(string filename) : assemblyFile(filename) {
		DEST = COMP = JUMP = "";
	}
	
	bool Parser::hasMoreCommands() {
		return (assemblyFile.peek() != EOF);
	}
	
	string Parser::advance() {
		getline(assemblyFile, currentCommand);
		char type = commandType();
		if(type == 'C') setDestCompJump();
		return currentCommand;
	}
	
	char Parser::commandType() {
		int i = 0;
		while(currentCommand[i] == ' ' || currentCommand[i] == '\t') i++;
		
		if(currentCommand[i] == '@') return A_COMMAND;      // @symbol
		if(currentCommand[i] == '(') return L_COMMAND;	  // (symbol)
		if(currentCommand[i] == '/') return COMMENT;	  // //comment
		if(i == currentCommand.length()) return BLANK;  // blank line
		return C_COMMAND;									  // dest = comp; jump
	}
	
	string Parser::symbol () {
		string addr = "";
		
		for(int i = 0; i < currentCommand.length(); i++) {
			char c = currentCommand[i];
			if(c == ' ' || c == '(' || c == '@') continue;
			else if(c == ')' || c == '/') break;
			addr += c;
		}
		return addr;
	}
	
	string Parser::dest() {
		return DEST;
	}
	
	string Parser::comp() {
		return COMP;
	}
	
	string Parser::jump() {
		return JUMP;
	}
	
	void Parser::setDestCompJump() {
		vector<string> tokens;
		
		DEST = COMP = JUMP = "";
		string tok;
		bool first = true;
		string cmd = "";	
		for(int i = 0; i < currentCommand.length(); i++) {
			char c = currentCommand[i];
			if(c == ' ' || c == '\t') continue;
			if(c == '=') {
				if(tok.length() != 0) {
					tokens.push_back(tok);
					DEST = tok;
				}
				tok = "";
				cmd += c;
				
			}
			else if(c == ';') {
				if(tok.length() != 0) {
					tokens.push_back(tok);
					COMP = tok;
				}
				tok = "";
				cmd += c;
			}
			else if(c == '/') {
				if(tok.length() != 0) {
					tokens.push_back(tok);
					if(COMP.length() == 0)
						COMP = tok;
					else
						JUMP = tok;
				}
				tok = "";
				if(i > 0 && currentCommand[i-1] == '/') {
					break;
				}
			}
			else {
				tok += c;
				cmd += c;
			}
		}
		if(tok.length() != 0) {
			tokens.push_back(tok);
			if(COMP.length() == 0)
				COMP = tok;
			else
				JUMP = tok;
		}
		//cout << "new Instruction ---------------------------------" << endl << endl;
		//cout << "tok: " << tok << " size: " << tok.length() << endl << endl;	
		//cout << cmd << endl;
		//cout << "dest: "  << DEST << ", comp: " << COMP << ", jump: " << JUMP << endl << endl;
		//for (string s : tokens) {
		//	cout << s << ", ";
		//}
		//cout << endl;
	}
	
	void Parser::helper() {
		while(getline(assemblyFile, currentCommand)) {
			char type = commandType();
			cout << "----------------------------------------------" << endl;
			cout << "Instr: " << currentCommand << endl;
			if(type == C_COMMAND) {
				setDestCompJump();
				cout << "dest: " << dest() << ", comp: " << comp() << ", jump: " << jump() << endl;
			}
			else if(type == A_COMMAND || type == L_COMMAND){
				cout << "symbol: " << symbol() << endl;
			}
			cout << endl;
		}
	}

	void Parser::reset() {
		assemblyFile.clear();
		assemblyFile.seekg(0, assemblyFile.beg);
	}	
	Parser::~Parser() {
		assemblyFile.close();
	}


