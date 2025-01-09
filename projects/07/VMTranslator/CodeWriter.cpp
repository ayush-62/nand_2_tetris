#include "CodeWriter.h"

using namespace std;

CodeWriter::CodeWriter(string outputFile) : asmFile(outputFile) { 
	// asmFileName = outputFile;
	debug = false;
}
		
void CodeWriter::setFileName(string file) {
	// close();
	// asmFile.open(file);
	currentVmFile = file;
	string str = "\n// **************************************    " + currentVmFile + ".vm code started!    **************************************\n\n";
	asmFile << str;
}
		
void CodeWriter::writeArithmetic(string cmd) {
	string asmCode = "";
	asmCode += "// " + cmd + "\n";
	if(cmd == "add" || cmd == "sub"  || cmd == "and"  || cmd == "or") {
		// add, sub, and, or
		asmCode += arithmetic_logical(cmd); 
	}
	else if(cmd == "neg" || cmd == "not"){
		// neg, not
		asmCode += neg_or_not(cmd);
	}
	else {
		// eq, gt, lt
		asmCode += comparision(cmd);
	}

	if(debug) cout << asmCode << endl;
	
	asmFile << asmCode;
}
		
void CodeWriter::writePushPop(string cmd, string segment, int index) {
	string asmCode = "";
	if(cmd == "push") {
		// push segment i
		asmCode = generateAsmPush(segment, index); 
	}
	else {
		//pop segment i
		asmCode = generateAsmPop(segment, index);
	}

	if(debug) cout << asmCode << endl;

	asmFile << asmCode;
}

void CodeWriter::close() {
	string endCode = "// Infinite Loop \n";
	endCode = "(END) \n";
	endCode += "@END \n";
	endCode += "0 ; JMP \n";
	
	asmFile << endCode;
		
	asmFile.close();
	asmFile.clear();
}

void CodeWriter::setDebug(bool dbg) { debug = dbg; }


// helper methods

string CodeWriter::generateAsmPush(string segment, int index) {
	string i = to_string(index);
	
	string asmCode = "// push " + segment + " " + to_string(index) + "\n"; 
	
	// push constant i -> [ *SP = i, SP++ ]
	if(segment == "constant") {
		asmCode += i_to_ptr(SP, i); 			// *sp = i
		asmCode += inc_or_dcr_vrb(SP, INC); 	// SP++
	}
	
	// push local i -> [ addr = LCL+i, *SP = *addr, SP++ ](Same for argument, this, that)
	// push temp i -> [ addr = 5+i, *SP = *addr, SP++ ]
	else if(segment == "local" || segment == "argument" || segment == "this" || segment == "that" || segment == "temp") {
		string seg = "";
		if(segment == "local") seg = LCL;
		else if(segment == "argument") seg = ARG;
		else if(segment == "this") seg = THIS;
		else if(segment == "that") seg = THAT;
		else seg = TEMP; 
		
		asmCode += i_th_segment(addr, seg, i);	//addr = SEG + i
		asmCode += ptr_to_ptr(SP, addr);		// *SP = *addr
		asmCode += inc_or_dcr_vrb(SP, INC);		// SP++
	}
	
	// push pointer 0/1 -> [ *SP = THIS/THAT, SP++ ]
	else if(segment == "pointer") {
		string th = "";
		if(index == 0) th = THIS;
		else th = THAT;
		
		asmCode += vrb_to_ptr(SP, th); 		// *SP = THIS/THAT
		asmCode += inc_or_dcr_vrb(SP, INC);	// SP++
	}
	
	// push static i -> [ *SP = File.i, SP++ ]
	else {
		string static_vrb = currentVmFile + "." + i;
		asmCode += vrb_to_ptr(SP, static_vrb);	// *SP File.i
		asmCode += inc_or_dcr_vrb(SP, INC);		// SP++
	}
	
	return asmCode;
}
		
string CodeWriter::generateAsmPop(string segment, int index) {
	string i = to_string(index);
	
	string asmCode = "// pop " + segment + " " + i + "\n"; 
	
	// pop local i -> [ addr = LCL+i, SP--, *addr = *SP ](Same for argument, this, that)
	// pop temp i -> [ addr = 5+i,  SP--, *addr = *SP ]
	if(segment == "local" || segment == "argument" || segment == "this" || segment == "that" || segment == "temp") {
		string seg = "";
		if(segment == "local") seg = LCL;
		else if(segment == "argument") seg = ARG;
		else if(segment == "this") seg = THIS;
		else if(segment == "that") seg = THAT;
		else seg = TEMP; 
		
		asmCode += i_th_segment(addr, seg, i);	//addr = SEG + i
		asmCode += inc_or_dcr_vrb(SP, DCR);		// SP--
		asmCode += ptr_to_ptr(addr, SP);		// *addr = *SP	
	}
	
	// pop pointer 0/1 -> [ SP--, THIS/THAT = *SP ]
	else if(segment == "pointer") {
		string th = "";
		if(index == 0) th = THIS;
		else th = THAT;
		
		asmCode += inc_or_dcr_vrb(SP, DCR);	// SP--
		asmCode += ptr_to_vrb(th, SP); 		// THIS/THAT = *SP
	}
	
	// push static i -> [ SP--, File.i = *SP ]
	else {
		string static_vrb = currentVmFile + "." + i;
		asmCode += inc_or_dcr_vrb(SP, DCR); 	// SP--
		asmCode += ptr_to_vrb(static_vrb, SP);	// File.i = *SP		
	}
	
	return asmCode;
}

// *ptr = i
string CodeWriter::i_to_ptr(string ptr, string i) {
	string code = "";
	// [ *SP = i]
	code += "@" + i + " \n"; 	// @i
	code += "D = A \n";  		// D = A
	code += "@" + ptr + " \n";  // @ptr 
	code += "A = M \n";  		// A = M
	code += "M = D \n"; 		// M = D
	
	return code;
}

// *ptr1 = *ptr
string CodeWriter::ptr_to_ptr(string ptr1, string ptr2) {
	string code = "";
	// [ *SP = *addr]
	code += "@" + ptr2 + " \n"; // @ptr2
	code += "A = M \n";  		// A = M
	code += "D = M \n";  		// D = M 
	code += "@" + ptr1 + " \n"; // @ptr1
	code += "A = M \n";  		// A = M
	code += "M = D \n";  		// M = D
	
	return code;
}

// *ptr = vrb
string CodeWriter::vrb_to_ptr(string ptr, string vrb) {
	string code = "";
	// [ *sp = Foo.i ]
	code += "@" + vrb + " \n";	// @vrb
	code += "D = M \n";			// D = M 
	code += "@" + ptr + " \n";  // @ptr
	code += "A = M \n";  		// A = M
	code += "M = D \n";  		// M = D
	
	return code;
}

// vrb = *ptr
string CodeWriter::ptr_to_vrb(string vrb, string ptr) {
	string code = "";
	// [ Foo.i = *SP]
	code += "@" + ptr + " \n"; 	// @ptr
	code += "A = M \n";  		// A = M
	code += "D = M \n";  		// D = M 
	code += "@" + vrb + " \n"; 	// @vrb
	code += "M = D \n";  		// M = D
	
	return code;
}

//vrb++ or vrb--
string CodeWriter::inc_or_dcr_vrb(string vrb, bool inc) {
	string code = "";
	// sp++ or sp--
	code += "@" + vrb + " \n"; 		// @vrb
	if(inc)	
		code += "M = M + 1 \n";  	// M = M + 1
	else
		code += "M = M - 1 \n";  	// M = M - 1	
	
	return code;
}

// [ addr = lcl + i ] or [ addr = 5 + i ]
string CodeWriter::i_th_segment(string dest, string segment, string i) {
	string code = "";
	// [ addr = LCL + i]
	code += "@" + i + " \n"; 		// @i
	code += "D = A \n";  			// D = A
	code += "@" + segment + " \n";  // @5 or @LCL
	if(segment == "5") {				// for [ addr = 5 + i ] 
		code += "D = D + A \n"; 		// D = D + A
	}
	else {								// for [ addr = LCL + i ]
		code += "D = D + M \n"; 		// D = D + M	
	}
	code += "@" + dest + " \n";  	// @addr
	code += "M = D \n";  			// M = D
	
	return code;
}

// add, sub, and, or
string CodeWriter::arithmetic_logical(string opr) {
	string asmCode = "";
	asmCode += inc_or_dcr_vrb(SP, DCR);	// SP--
	asmCode += "A = M \n";				// A = M
	asmCode += "D = M \n";				// D = M
	asmCode += inc_or_dcr_vrb(SP, DCR);	// SP--
	asmCode += "A = M \n";				// A = M
	if(opr == "add")
		asmCode += "D = D + M \n";		// D = D + M   	------ addition
	else if(opr == "sub"){
		asmCode += "D = D - M \n";		// D = D - M   	d = y-x
		asmCode += "D = -D \n";			// D = -D		-d = x-y ------ subtraction
	}
	else if(opr == "and")
		asmCode += "D = D & M \n";		// D = D & M   	------ and
	else
		asmCode += "D = D | M \n";		// D = D | M   	------ or
	asmCode += "M = D \n";				// M = D 		------ saving back to stack
	asmCode += inc_or_dcr_vrb(SP, INC);	// SP++
 
	return asmCode;
} 

// neg, not
string CodeWriter::neg_or_not(string opr) {
	string asmCode = "";
	asmCode += inc_or_dcr_vrb(SP, DCR);	// SP--
	asmCode += "A = M \n";				// A = M
	asmCode += "D = M \n";				// D = M
	if(opr == "neg")
		asmCode += "M = -D \n";				// M = -D		neg
	else						
		asmCode += "M = !D \n";				// M = !D		not
	asmCode += inc_or_dcr_vrb(SP, INC);	// SP++

	return asmCode;
}

// eq, lt, gt, 
string CodeWriter::comparision(string cmp) {
	string asmCode = "", jmp = "";

	string label_t = "TRUE" + to_string(label_no);
	string label_f = "FALSE" + to_string(label_no++);

	if(cmp == "eq") jmp = "JEQ";		// eq
	else if(cmp == "lt") jmp = "JGT";	// lt
	else jmp = "JLT"; 					// gt

	asmCode += inc_or_dcr_vrb(SP, DCR);	// SP--
	asmCode += "A = M \n";				// A = M
	asmCode += "D = M \n";				// D = M
	asmCode += inc_or_dcr_vrb(SP, DCR);	// SP--
	asmCode += "A = M \n";				// A = M
	asmCode += "D = D - M \n";			// D = D - M
	asmCode += "@" + label_t + "\n";	// @TRUE			true== 0, false = -1
	asmCode += "D ; " +  jmp + " \n";	// D ; JEQ/JGT/JLT
	asmCode += "D = 0 \n";				// D = -1
	asmCode += "@" + label_f + "\n";	// @FALSE			
	asmCode += "0 ; JMP \n";			// 0 ; JMP
	asmCode += "(" + label_t + ") \n";	// (TRUE)
	asmCode += "D = -1 \n";				// D = 0
	asmCode += "(" + label_f + ") \n";	// (FALSE)
	asmCode += "@SP \n";				// @SP
	asmCode += "A = M \n";				// A = M
	asmCode += "M = D \n";				// M = D
	asmCode += inc_or_dcr_vrb(SP, INC);	// SP++

	return asmCode;
}


string CodeWriter::getBaseFileName(string filename) {
	string basename = "";
	filename.substr(0, asmFileName.length()-4);
	for(int i = filename.length()-4; i >= 0 && filename[i] != '\\' && filename[i] != '/'; i--) {
		basename = filename[i] + basename;
	}
	return basename;
}

/*
Constructor - Output file / stream -- Opens the output file/stream and gets ready to write into it.

setFileName - fileName (string) -- Informs the code writer that the translation of a new VM file is started.

writeArithmetic - command (string) -- Writes the assembly code that is the translation of the given arithmetic command.

WritePushPop - command (C_PUSH or C_POP),segment (string),index (int) -- Writes the assembly code that is the translation
				of the given command, where command is either C_PUSH or C_POP.

Close -- -- Closes the output file
*/
