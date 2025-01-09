// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
//
// This program only needs to handle arguments that satisfy
// R0 >= 0, R1 >= 0, and R0*R1 < 32768.

// Put your code here.

// Psuedo Code: 
//		R0, R1, R2
// 		mul = R0
//		i = 0
//   LOOP:
//		if i == num2 Jmp END
//		mul = mul + num1
//		i = i + 1
// 		jmp LOOP;
//
//	END: 
//		R2 = mul
// 		Halt;

	@R0
	D = M
	@mul		
	M = 0		// mul  = R0	
	
	@i			 
	M = 0		// i = 0
	
(LOOP)
	@i   
	D = M
	@R1
	D = D - M
	@EXIT
	D; JEQ   	// if i == R1 then jmp to EXIT
	
	@R0
	D = M
	@mul
	M = D + M 	// mul = mul + R0
	
	@i
	M = M + 1	// i = i + 1
	
	@LOOP
	0; JMP		// goto LOOP
	
(EXIT)
	@mul
	D = M
	@R2
	M = D

(END)
	@END
	0;JMP 		// Infinite loop
	

