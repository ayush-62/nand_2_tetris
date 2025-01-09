#include <iostream>
#include <fstream>
#include <bitset>
#include "Parser.h"
#include "Code.h"
#include "SymbolTable.h"

using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	string fileName = ".\\max\\Max.asm";
	bool debug = false;
	
	if(argc > 1) fileName = argv[1];
	if(argc > 2) debug = (argv[2][0] == '1'); 
	 
	if(debug) cout << "file: " << fileName << endl << endl;
	Parser parser(fileName);
	SymbolTable symbol_table;
	
	if(debug) cout << "file Loaded!" << endl;
	
	if(debug) cout << "********************   First Pass!   *****************************" << endl << endl;
	//first pass
	int lineNumber = 0;
	while (parser.hasMoreCommands()) {
		parser.advance();
		//cout << "------------------------------------" << endl;
		//cout << "current Line: " << parser.currentCommand << endl << endl;
		if(parser.commandType() == C_COMMAND) {
			if(debug) cout << lineNumber << " dest: " << parser.dest() << ", comp: " << parser.comp() << ", jump: " << parser.jump() << endl;
			lineNumber++;
		}
		else if(parser.commandType() == A_COMMAND){
			if(debug) cout << lineNumber << " Address: " << parser.symbol() << endl;
			lineNumber++;
		}
		else if(parser.commandType() == L_COMMAND){
			if(debug) cout << "Label: " << parser.symbol() << endl;
			symbol_table.addEntry(parser.symbol(), lineNumber);	
		}
		else continue;
		if(debug) cout << endl;
	}
	
//	for(auto e : symbol_table.symtbl) {
//		cout << e.first << " -> " << e.second << endl;
//	}

	if(debug) cout << "********************   Second Pass!   *****************************" << endl << endl;
	// resetting for second pass
	parser.reset();
	
	vector<string> machine_code;
	//second pass
	lineNumber = 0;
	int ram_location = 16;
	while (parser.hasMoreCommands()) {
		parser.advance();
		//cout << "------------------------------------" << endl;
		//cout << "current Line: " << parser.currentCommand << endl << endl;
		if(parser.commandType() == C_COMMAND) {
			if(debug) cout << lineNumber << " dest: " << parser.dest() << ", comp: " << parser.comp() << ", jump: " << parser.jump() << endl;
			string cmd = "111" + Code::comp(parser.comp()) + Code::dest(parser.dest()) + Code::jump(parser.jump());
			machine_code.push_back(cmd);
			lineNumber++;
		}
		else if(parser.commandType() == A_COMMAND){
			string symbol = parser.symbol();
			string cmd = "";
			if(debug) cout << lineNumber << " Address: " << symbol << endl;
			if(isalpha(symbol[0])) {
				if(symbol_table.contains(symbol)) {
					cmd = "0" + bitset<15>(symbol_table.getAddress(symbol)).to_string();
				}
				else {
					cmd = "0" + bitset<15>(ram_location).to_string();
					symbol_table.addEntry(symbol, ram_location);
					ram_location++;
				}
			} 
			else {
				cmd = "0" + bitset<15>(stoi(symbol)).to_string();
			}
			machine_code.push_back(cmd);
			lineNumber++;
		}
		else if(parser.commandType() == L_COMMAND){
			if(debug) cout << "Ignore Label: " << parser.symbol() << endl;
		}
		else continue;
		if(debug) cout << endl;
	}
	
	string outfile = fileName.substr(0, fileName.length()-4) + ".hack";
	if(debug) cout << "Output File: " << outfile << endl << endl;
	ofstream hackfile(outfile);
	
	for(string cmd : machine_code) {
		hackfile << cmd << endl;
		if(debug) cout << cmd << endl;
	}
	if(debug) cout << endl;
	hackfile.close();
	
	if(debug) cout << "Assebly Ended!" << endl;
	return 0;
}








