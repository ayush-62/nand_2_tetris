#include "SymbolTable.h"

using namespace std;

SymbolTable::SymbolTable() {
	symtbl["SP"] = 0;
	symtbl["LCL"] = 1;
	symtbl["ARG"] = 2;
	symtbl["THIS"] = 3;
	symtbl["THAT"] = 4;
	
	symtbl["R0"] = 0;
	symtbl["R1"] = 1;
	symtbl["R2"] = 2;
	symtbl["R3"] = 3;
	symtbl["R4"] = 4;
	symtbl["R5"] = 5;
	symtbl["R6"] = 6;
	symtbl["R7"] = 7;
	symtbl["R8"] = 8;
	symtbl["R9"] = 9;
	symtbl["R10"] = 10;
	symtbl["R11"] = 11;
	symtbl["R12"] = 12;
	symtbl["R13"] = 13;
	symtbl["R14"] = 14;
	symtbl["R15"] = 15;
	
	symtbl["SCREEN"] = 16384;
	symtbl["KBD"] = 24576;
}

void SymbolTable::addEntry(string label, int address) {
	symtbl[label] = address;
}
	
bool SymbolTable::contains(string label) {
	return (symtbl.find(label) != symtbl.end());
}
	
int SymbolTable::getAddress(string label) {
	return symtbl[label];
}
