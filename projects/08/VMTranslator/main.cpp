#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include "Parser.h"
#include "CodeWriter.h"

using namespace std;

namespace fs = std::filesystem;

void translate(Parser &parser, CodeWriter &codeWriter, fs::path vmfile);

bool debug = true;


int main(int argc, char** argv) {
	std::cout << "c++ version: " << __cplusplus << std::endl;

	string vmfile = "../StackArithmetic/StackTest";
	
	if(argc > 1) vmfile = argv[1];
	if(argc > 2) debug = (argv[2][0] == '1'); 

	fs::path vm_path(vmfile);
	fs::path d_path;
	fs::path asm_path;

	vm_path.make_preferred();
	d_path.make_preferred();
	asm_path.make_preferred();

	if(fs::is_directory(vm_path)) {
		if(vm_path.has_stem()) {
			d_path = vm_path;
		}
		else {
			d_path = vm_path.parent_path();
		}
		asm_path = d_path; 
		asm_path /= asm_path.stem().string()+".asm";
	}
	else {
		d_path = vm_path.parent_path();
		asm_path = vm_path;
		asm_path.replace_extension("asm");
	}

	cout << "vm_path: " << vm_path.string() << endl;
	cout << "d_path: " << d_path.string() << endl;
	cout << "asm_path: " << asm_path.string() << endl << endl;

	// Parser and code writer 
	Parser parser(vmfile);
	CodeWriter codeWriter(fs::absolute(asm_path).string());
	
	if(fs::is_directory(vm_path)) {
		for(auto file : fs::directory_iterator(d_path)) {
			if(debug) cout << "----------------------------------------------------------------------------" << endl;
			if(debug) cout << "File: " << file.path().string() << endl;
			if(file.path().extension() != ".vm") continue;
			translate(parser, codeWriter, file.path());
		}
	}
	else {
		translate(parser, codeWriter, vm_path);
	}

	codeWriter.close();
	if(debug) cout << "VM Translation Ended!" << endl;
	return 0;
}

void translate(Parser &parser, CodeWriter &codeWriter, fs::path vmfile) {

	parser.setFile(fs::absolute(vmfile).string());
	codeWriter.setFileName(vmfile.stem().string());

	int lineNumber = 0;
	while (parser.hasMoreCommands()) {
		string currentCommand = parser.advance();
		if(parser.commandType() == C_ARITHMETIC) {
			if(debug) cout << "[" << lineNumber << "] Arithmetic: " << currentCommand << endl;
			codeWriter.writeArithmetic(parser.arg1());
		}
		else if(parser.commandType() == C_PUSH){
			if(debug) cout << "["  << lineNumber << "] Push: " << currentCommand << endl;
			codeWriter.writePushPop("push", parser.arg1(), parser.arg2()); 
		}
		else if(parser.commandType() == C_POP){
			if(debug) cout << "[" << lineNumber << "] Pop: " << currentCommand << endl; 	
			codeWriter.writePushPop("pop", parser.arg1(), parser.arg2());
		}
		else if(parser.commandType() == C_LABEL){
			cout << "[" << lineNumber << "] Label: " << currentCommand << endl; 	
			codeWriter.writeLabel(parser.arg1());
		}
		else if(parser.commandType() == C_GOTO){
			if(debug) cout << "[" << lineNumber << "] Goto: " << currentCommand << endl; 	
			codeWriter.writeGoto(parser.arg1());
		}
		else if(parser.commandType() == C_IF){
			if(debug) cout << "[" << lineNumber << "] IF-Goto: " << currentCommand << endl; 	
			codeWriter.writeIf(parser.arg1());
		}
		else if(parser.commandType() == C_FUNCTION){
			if(debug) cout << "[" << lineNumber << "] Function: " << currentCommand << endl; 	
			codeWriter.writeFunction(parser.arg1(), parser.arg2());
		}
		else if(parser.commandType() == C_CALL){
			if(debug) cout << "[" << lineNumber << "] Fn Call: " << currentCommand << endl; 	
			codeWriter.writeCall(parser.arg1(), parser.arg2());
		}
		else if(parser.commandType() == C_RETURN){
			if(debug) cout << "[" << lineNumber << "] Return: " << currentCommand << endl; 	
			codeWriter.writeReturn();
		}
		else continue;
		
		if(debug) parser.printStatus();

		lineNumber++;
		if(debug) cout << endl;
	}
	cout << vmfile.filename() << " -> done!" << endl << endl;
}








