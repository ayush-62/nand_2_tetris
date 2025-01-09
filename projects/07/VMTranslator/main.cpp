#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include "Parser.h"
#include "CodeWriter.h"

using namespace std;

namespace fs = std::filesystem;

void translate(Parser &parser, CodeWriter &codeWriter, fs::path vmfile);

string files[] = {
	"../StackArithmetic/SimpleAdd/SimpleAdd.vm",
	"../StackArithmetic/StackTest/StackTest.vm",
	"../MemoryAccess/BasicTest/BasicTest.vm",
	"../MemoryAccess/StaticTest/StaticTest.vm",
	"../MemoryAccess/PointerTest/PointerTest.vm"
};

bool debug = false;

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
		if(debug) parser.printStatus();
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
		else continue;
		
		lineNumber++;
		if(debug) cout << endl;
	}
	cout << vmfile.filename() << " -> done!" << endl << endl;
}








