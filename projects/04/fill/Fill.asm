// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Put your code here.

//	START: 
//		if keyboard == 0 jmp white
//	
//	BLACK:
//		color = -1
//		jmp INIT
//
//	WHITE:
//		color = 0
//
//	INIT
//		n = 8192
//		i = 0
//	LOOP:
//		if i == n then START
//		screen[i] = -1
//		i = i + 1
//		jmp LOOP;	


(START)
	@KBD
	D = M
	@WHITE
	D; JEQ 		// if KEYBOARD = 0 then goto WHITE
	
	@color
	M = -1
	@INIT
	0; JMP		// else color = -1 goto INIT
	
(WHITE)
	@color
	M = 0		// color = 0

(INIT)
	@8192
	D = A
	@n
	M = D		// n = 8192
		
	@SCREEN
	D = A
	@current
	M = D		// current = screen(16384)
	
	@i
	M = 0		// i = 0

(LOOP)
	@i
	D = M
	@n
	D = D - M
	@START
	D; JEQ		// if i = 0 then goto START
	
	@color
	D = M
	@current
	A = M
	M = D 		// screen[current] = color
	
	@current
	M = M + 1	// current = current + 1
	@i
	M = M + 1	// i = i + 1
	@LOOP
	0; JMP		// goto LOOP
	
	
	
	
	
	
	
	