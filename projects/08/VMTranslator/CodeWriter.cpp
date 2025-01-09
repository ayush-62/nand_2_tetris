#include "CodeWriter.h"

using namespace std;

CodeWriter::CodeWriter(string outputFile) : asmFile(outputFile) { 
	// asmFileName = outputFile;
	label_no = return_label_no = 0;
	debug = false;

	string init = "// ####################################       Program Initialization  ####################################       \n";
	init += "@256 \n";
	init += "D = A \n";
	init += "@SP \n";
	init += "M = D \n"; // SP = 256;
	init += "@ARG \n";
	init += "M = D \n";  // ARG = 256;
	init += generateCall("Sys.init", 0);

	asmFile << init;
}
		
void CodeWriter::setFileName(string file) {
	// close();
	// asmFile.open(file);
	currentVmFile = file;
	string str = "\n// **************************************    " + currentVmFile + ".vm code started!    **************************************\n\n";
	cout << "CodeWriter ->  set File name: " << file  << endl;
	asmFile << str;
}
		
void CodeWriter::writeArithmetic(string cmd) {
	string asmCode = "";
	asmCode += "// ------------------------------   " + cmd + "   ------------------------------\n";
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

void CodeWriter::writeLabel(string label) {
	label = current_function + "." + label;
	string asmCode = generateLabel(label);
	asmFile << asmCode;
}
				
void CodeWriter::writeGoto(string label) {
	label = current_function + "." + label;
	string asmCode = generateGoto(label);
	asmFile << asmCode;
}

void CodeWriter::writeIf(string label) {
	label = current_function + "." + label;
	string asmCode = generateIf(label);	// label LABEL
	asmFile << asmCode;
}

void CodeWriter::writeFunction(string function_name, int nVars) {
	string asmCode = generateFunction(function_name, nVars);
	asmFile << asmCode; 
}

void CodeWriter::writeCall(string function_name, int nArgs) {
	string asmCode = generateCall(function_name, nArgs);
	asmFile << asmCode;	
}

void CodeWriter::writeReturn() {
	string asmCode = generateReturn();
	asmFile << asmCode;
}

void CodeWriter::close() {	
	asmFile.close();
	asmFile.clear();
}

void CodeWriter::setDebug(bool dbg) { debug = dbg; }


// helper methods

// generates asm code for push statement 
string CodeWriter::generateAsmPush(string segment, int index) {
	string i = to_string(index);
	
	string asmCode = "// ------------------------------   push " + segment + " " + to_string(index) + "   ------------------------------\n"; 
	
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
		
// generates asm code for pop statement
string CodeWriter::generateAsmPop(string segment, int index) {
	string i = to_string(index);
	
	string asmCode = "// ------------------------------   pop " + segment + " " + i + "   ------------------------------\n"; 
	
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

// generates asm code for label statement
string CodeWriter::generateLabel(string label) {
	string asmCode = "// ------------------------------   label " + label + "   ------------------------------\n"; // comment - actual vm command
	asmCode += "(" + label + ")\n";	// (LABEL)
	
	return asmCode;
}

// generates asm code for goto statement
string CodeWriter::generateGoto(string label) {
	string asmCode = "// ------------------------------   goto " + label + "   ------------------------------\n";	// comment - actual vm command
	
	asmCode += "@" + label + "\n";	// @LABEL
	asmCode += "0 ; JMP\n";			// 0 ; JMP

	return asmCode;
}

// generates asm code for if-goto statement
string CodeWriter::generateIf(string label) {
	string asmCode = "// ------------------------------   if-goto " + label + "   ------------------------------\n";	// comment - actual vm command
	
	asmCode += "@" + SP + "\n";		// @SP
	asmCode += "M = M - 1 \n";		// M = M - 1
	asmCode += "A = M \n";			// A = M
	asmCode += "D = M \n";			// D = M
	asmCode += "@" + label + "\n";	// @LABEL
	asmCode += "D ; JNE\n";			// D ; JNE

	return asmCode;
}

// generates asm code for call statement
string CodeWriter::generateCall(string function_name, int nArgs) {
	string asmCode = "// ------------------------------   call " + function_name + " " + to_string(nArgs) + "   ------------------------------\n";

	string return_label = "RETURN"+ to_string(return_label_no++) + "." + function_name;
	asmCode += sym_push(return_label); 	// @RETURN push RETURN;
	asmCode += vrb_push(LCL);			// push LCL;
	asmCode += vrb_push(ARG);			// push ARG;
	asmCode += vrb_push(THIS); 			// push THIS;
	asmCode += vrb_push(THAT); 			// push THAT;

	int i = nArgs + 5;			// ------- [i = nArgs + 5] -------
	asmCode += i_th_segment(ARG, SP, to_string(-i)); // ARG = SP - nArgs - 5
	asmCode += vrb_to_vrb(LCL, SP);			// LCL = SP
	asmCode += generateGoto(function_name);	// goto FUNCTION
	asmCode += generateLabel(return_label); // (RETURN)

	return asmCode;
}

// generates asm code for function statement
string CodeWriter::generateFunction(string function_name, int nVars) {
	string asmCode = "// ------------------------------   function " + function_name + " " + to_string(nVars) + "   ------------------------------\n";
	
	current_function = function_name;

	asmCode += "(" + function_name + ") \n";	// (FUNCTION)
	for(int i = 0; i < nVars; i++) { 			// repeat nVars times
		asmCode += i_to_ptr(SP, to_string(0));	// *SP = 0
		asmCode += inc_or_dcr_vrb(SP, INC);		// SP++
	}

	return asmCode;
}

// generates asm code for return statement
string CodeWriter::generateReturn() {
	string asmCode = "// ------------------------------   return   ------------------------------\n";

	string ret = "R13",  frame = "R14", temp = "R15";
	asmCode += vrb_to_vrb(frame, LCL);				// frame = LCL		--- R15 = FRAME
	asmCode += i_th_segment(frame, frame, to_string(-5));// frame = frame - 5	--- R15 = FRAME - 5
	asmCode += ptr_to_vrb(ret, frame);				// Ret = *(frame)		--- R13 = RET
	asmCode += inc_or_dcr_vrb(SP, DCR);				// SP--
	asmCode += ptr_to_ptr(ARG, SP);					// *ARG = *SP
	asmCode += i_th_segment(SP, ARG, to_string(1));	// SP = ARG + 1
	asmCode += inc_or_dcr_vrb(frame, INC);			// frame++			--- R14 = FRAME - 4
	asmCode += ptr_to_vrb(LCL, frame);				// LCL = *frame
	asmCode += inc_or_dcr_vrb(frame, INC);			// frame++			--- R14 = FRAME - 3
	asmCode += ptr_to_vrb(ARG, frame);				// ARG = *frame
	asmCode += inc_or_dcr_vrb(frame, INC);			// frame++			--- R14 = FRAME - 2
	asmCode += ptr_to_vrb(THIS, frame);				// THIS = *frame
	asmCode += inc_or_dcr_vrb(frame, INC);			// frame++			--- R14 = FRAME - 1
	asmCode += ptr_to_vrb(THAT, frame);				// THAT = *frame
	asmCode += "@" + ret + "\n";					// @ret
	asmCode += "A = M \n";							// A = M
	asmCode += "0 ; JMP \n";						// 0 ; JMP

	return asmCode;
}


// push variable to stack
// [ *SP = VRB, SP++ ]
string CodeWriter::vrb_push(string vrb) {
	string code = "";
	code += vrb_to_ptr(SP, vrb);	// *SP = VRB
	code += inc_or_dcr_vrb(SP, INC);// SP++

	return code;
}

// push label address to stack
// [ *SP = @RET, SP++ ]
string CodeWriter::sym_push(string sym) {
	string code = "";
	code += "@" + sym + " \n"; 	// @RETURN push RETURN;
	code += "D = A \n";					// D = A    ---> push RETURN
	code += "@SP \n";
	code += "A = M \n";
	code += "M = D \n";
	code += inc_or_dcr_vrb(SP, INC);

	return code;
}

// *ptr = i
string CodeWriter::i_to_ptr(string ptr, string i) {
	string code = "";
	// [ *SP = i]
	if(i != "0" && i != "1") {
		code += "@" + i + " \n"; 	// @i
		code += "D = A \n";  		// D = A
	}
	code += "@" + ptr + " \n";  // @ptr 
	code += "A = M \n";  		// A = M
	if(i == "0" || i == "1")
		code += "M = " + i + " \n"; 		// M = 0 or M = 1
	else
		code += "M = D \n"; 		// M = D
	
	return code;
}

// vrb1 = vrb2
string CodeWriter::vrb_to_vrb(string vrb1, string vrb2) {
	string code = "";
	// [ LCL = SP ]
	code += "@" + vrb2 + " \n";	// @vrb2
	code += "D = M \n";			// D = M 
	code += "@" + vrb1 + " \n"; // @vrb1
	code += "M = D \n";  		// M = D
	
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

// [ addr = lcl + i ] or [ addr = lcl - i ] or [ addr = 5 + i ()]
// to access ith next or previous address from base adress ---- 5 is used for temp segment.
// [ addr = base_addr + i] or [ addr = base_addr - i] or [ addr = 5 + i]
// ******* 'i' is constant ********
string CodeWriter::i_th_segment(string dest, string segment, string in) {
	string code = "";
	int ind = stoi(in);
	string i = to_string(abs(ind));
	
	if(ind < -1 || ind > 1) {
		code += "@" + i + " \n"; 		// @i
		code += "D = A \n";  			// D = A
	}
	
	code += "@" + segment + " \n";  	// @5 or @LCL
	
	if(segment == TEMP) {
		if(ind == 0) 		{code += "D = A \n";}		// 5 + 0
		else if(ind == 1) 	{code += "D = A + 1 \n";}	// 5 + 1
		else if(ind == -1) 	{code += "D = A - 1 \n";}	// 5 - 1
		else if(ind > 1) 	{code += "D = D + A \n";}	// 5 + i
		else {
			code += "D = D + A \n";
			code += "D = -D \n";						// 5 - i
		}
	}
	else {
		if(ind == 0) 		{code += "D = M \n";}		// SEG + 0
		else if(ind == 1) 	{code += "D = M + 1 \n";}	// SEG + 1
		else if(ind == -1) 	{code += "D = M - 1 \n";}	// SEG - 1
		else if(ind > 1) 	{code += "D = D + M \n";}	// SEG + i
		else {
			code += "D = D - M \n";
			code += "D = -D \n";						// SEG - i
		}
	}

	code += "@" + dest + " \n";  	// @addr
	code += "M = D \n";  			// M = D			// addr = SEG +/- i  or  addr = 5 +/- i
	
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


/*
Constructor - Output file / stream -- Opens the output file/stream and gets ready to write into it.

setFileName - fileName (string) -- Informs the code writer that the translation of a new VM file is started.

writeArithmetic - command (string) -- Writes the assembly code that is the translation of the given arithmetic command.

WritePushPop - command (C_PUSH or C_POP),segment (string),index (int) -- Writes the assembly code that is the translation
				of the given command, where command is either C_PUSH or C_POP.

Close -- -- Closes the output file
*/
