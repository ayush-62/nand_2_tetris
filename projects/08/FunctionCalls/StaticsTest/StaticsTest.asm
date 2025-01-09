// ####################################       Program Initialization  ####################################       
@256 
D = A 
@SP 
M = D 
@ARG 
M = D 
// ------------------------------   call Sys.init 0   ------------------------------
@RETURN0.Sys.init 
D = A 
@SP 
A = M 
M = D 
@SP 
M = M + 1 
@LCL 
D = M 
@SP 
A = M 
M = D 
@SP 
M = M + 1 
@ARG 
D = M 
@SP 
A = M 
M = D 
@SP 
M = M + 1 
@THIS 
D = M 
@SP 
A = M 
M = D 
@SP 
M = M + 1 
@THAT 
D = M 
@SP 
A = M 
M = D 
@SP 
M = M + 1 
@5 
D = A 
@SP 
D = D - M 
D = -D 
@ARG 
M = D 
@SP 
D = M 
@LCL 
M = D 
// ------------------------------   goto Sys.init   ------------------------------
@Sys.init
0 ; JMP
// ------------------------------   label RETURN0.Sys.init   ------------------------------
(RETURN0.Sys.init)

// **************************************    Class1.vm code started!    **************************************

// ------------------------------   function Class1.set 0   ------------------------------
(Class1.set) 
// ------------------------------   push argument 0   ------------------------------
@ARG 
D = M 
@addr 
M = D 
@addr 
A = M 
D = M 
@SP 
A = M 
M = D 
@SP 
M = M + 1 
// ------------------------------   pop static 0   ------------------------------
@SP 
M = M - 1 
@SP 
A = M 
D = M 
@Class1.0 
M = D 
// ------------------------------   push argument 1   ------------------------------
@ARG 
D = M + 1 
@addr 
M = D 
@addr 
A = M 
D = M 
@SP 
A = M 
M = D 
@SP 
M = M + 1 
// ------------------------------   pop static 1   ------------------------------
@SP 
M = M - 1 
@SP 
A = M 
D = M 
@Class1.1 
M = D 
// ------------------------------   push constant 0   ------------------------------
@SP 
A = M 
M = 0 
@SP 
M = M + 1 
// ------------------------------   return   ------------------------------
@LCL 
D = M 
@R14 
M = D 
@5 
D = A 
@R14 
D = D - M 
D = -D 
@R14 
M = D 
@R14 
A = M 
D = M 
@R13 
M = D 
@SP 
M = M - 1 
@SP 
A = M 
D = M 
@ARG 
A = M 
M = D 
@ARG 
D = M + 1 
@SP 
M = D 
@R14 
M = M + 1 
@R14 
A = M 
D = M 
@LCL 
M = D 
@R14 
M = M + 1 
@R14 
A = M 
D = M 
@ARG 
M = D 
@R14 
M = M + 1 
@R14 
A = M 
D = M 
@THIS 
M = D 
@R14 
M = M + 1 
@R14 
A = M 
D = M 
@THAT 
M = D 
@R13
A = M 
0 ; JMP 
// ------------------------------   function Class1.get 0   ------------------------------
(Class1.get) 
// ------------------------------   push static 0   ------------------------------
@Class1.0 
D = M 
@SP 
A = M 
M = D 
@SP 
M = M + 1 
// ------------------------------   push static 1   ------------------------------
@Class1.1 
D = M 
@SP 
A = M 
M = D 
@SP 
M = M + 1 
// ------------------------------   sub   ------------------------------
@SP 
M = M - 1 
A = M 
D = M 
@SP 
M = M - 1 
A = M 
D = D - M 
D = -D 
M = D 
@SP 
M = M + 1 
// ------------------------------   return   ------------------------------
@LCL 
D = M 
@R14 
M = D 
@5 
D = A 
@R14 
D = D - M 
D = -D 
@R14 
M = D 
@R14 
A = M 
D = M 
@R13 
M = D 
@SP 
M = M - 1 
@SP 
A = M 
D = M 
@ARG 
A = M 
M = D 
@ARG 
D = M + 1 
@SP 
M = D 
@R14 
M = M + 1 
@R14 
A = M 
D = M 
@LCL 
M = D 
@R14 
M = M + 1 
@R14 
A = M 
D = M 
@ARG 
M = D 
@R14 
M = M + 1 
@R14 
A = M 
D = M 
@THIS 
M = D 
@R14 
M = M + 1 
@R14 
A = M 
D = M 
@THAT 
M = D 
@R13
A = M 
0 ; JMP 

// **************************************    Class2.vm code started!    **************************************

// ------------------------------   function Class2.set 0   ------------------------------
(Class2.set) 
// ------------------------------   push argument 0   ------------------------------
@ARG 
D = M 
@addr 
M = D 
@addr 
A = M 
D = M 
@SP 
A = M 
M = D 
@SP 
M = M + 1 
// ------------------------------   pop static 0   ------------------------------
@SP 
M = M - 1 
@SP 
A = M 
D = M 
@Class2.0 
M = D 
// ------------------------------   push argument 1   ------------------------------
@ARG 
D = M + 1 
@addr 
M = D 
@addr 
A = M 
D = M 
@SP 
A = M 
M = D 
@SP 
M = M + 1 
// ------------------------------   pop static 1   ------------------------------
@SP 
M = M - 1 
@SP 
A = M 
D = M 
@Class2.1 
M = D 
// ------------------------------   push constant 0   ------------------------------
@SP 
A = M 
M = 0 
@SP 
M = M + 1 
// ------------------------------   return   ------------------------------
@LCL 
D = M 
@R14 
M = D 
@5 
D = A 
@R14 
D = D - M 
D = -D 
@R14 
M = D 
@R14 
A = M 
D = M 
@R13 
M = D 
@SP 
M = M - 1 
@SP 
A = M 
D = M 
@ARG 
A = M 
M = D 
@ARG 
D = M + 1 
@SP 
M = D 
@R14 
M = M + 1 
@R14 
A = M 
D = M 
@LCL 
M = D 
@R14 
M = M + 1 
@R14 
A = M 
D = M 
@ARG 
M = D 
@R14 
M = M + 1 
@R14 
A = M 
D = M 
@THIS 
M = D 
@R14 
M = M + 1 
@R14 
A = M 
D = M 
@THAT 
M = D 
@R13
A = M 
0 ; JMP 
// ------------------------------   function Class2.get 0   ------------------------------
(Class2.get) 
// ------------------------------   push static 0   ------------------------------
@Class2.0 
D = M 
@SP 
A = M 
M = D 
@SP 
M = M + 1 
// ------------------------------   push static 1   ------------------------------
@Class2.1 
D = M 
@SP 
A = M 
M = D 
@SP 
M = M + 1 
// ------------------------------   sub   ------------------------------
@SP 
M = M - 1 
A = M 
D = M 
@SP 
M = M - 1 
A = M 
D = D - M 
D = -D 
M = D 
@SP 
M = M + 1 
// ------------------------------   return   ------------------------------
@LCL 
D = M 
@R14 
M = D 
@5 
D = A 
@R14 
D = D - M 
D = -D 
@R14 
M = D 
@R14 
A = M 
D = M 
@R13 
M = D 
@SP 
M = M - 1 
@SP 
A = M 
D = M 
@ARG 
A = M 
M = D 
@ARG 
D = M + 1 
@SP 
M = D 
@R14 
M = M + 1 
@R14 
A = M 
D = M 
@LCL 
M = D 
@R14 
M = M + 1 
@R14 
A = M 
D = M 
@ARG 
M = D 
@R14 
M = M + 1 
@R14 
A = M 
D = M 
@THIS 
M = D 
@R14 
M = M + 1 
@R14 
A = M 
D = M 
@THAT 
M = D 
@R13
A = M 
0 ; JMP 

// **************************************    Sys.vm code started!    **************************************

// ------------------------------   function Sys.init 0   ------------------------------
(Sys.init) 
// ------------------------------   push constant 6   ------------------------------
@6 
D = A 
@SP 
A = M 
M = D 
@SP 
M = M + 1 
// ------------------------------   push constant 8   ------------------------------
@8 
D = A 
@SP 
A = M 
M = D 
@SP 
M = M + 1 
// ------------------------------   call Class1.set 2   ------------------------------
@RETURN1.Class1.set 
D = A 
@SP 
A = M 
M = D 
@SP 
M = M + 1 
@LCL 
D = M 
@SP 
A = M 
M = D 
@SP 
M = M + 1 
@ARG 
D = M 
@SP 
A = M 
M = D 
@SP 
M = M + 1 
@THIS 
D = M 
@SP 
A = M 
M = D 
@SP 
M = M + 1 
@THAT 
D = M 
@SP 
A = M 
M = D 
@SP 
M = M + 1 
@7 
D = A 
@SP 
D = D - M 
D = -D 
@ARG 
M = D 
@SP 
D = M 
@LCL 
M = D 
// ------------------------------   goto Class1.set   ------------------------------
@Class1.set
0 ; JMP
// ------------------------------   label RETURN1.Class1.set   ------------------------------
(RETURN1.Class1.set)
// ------------------------------   pop temp 0   ------------------------------
@5 
D = A 
@addr 
M = D 
@SP 
M = M - 1 
@SP 
A = M 
D = M 
@addr 
A = M 
M = D 
// ------------------------------   push constant 23   ------------------------------
@23 
D = A 
@SP 
A = M 
M = D 
@SP 
M = M + 1 
// ------------------------------   push constant 15   ------------------------------
@15 
D = A 
@SP 
A = M 
M = D 
@SP 
M = M + 1 
// ------------------------------   call Class2.set 2   ------------------------------
@RETURN2.Class2.set 
D = A 
@SP 
A = M 
M = D 
@SP 
M = M + 1 
@LCL 
D = M 
@SP 
A = M 
M = D 
@SP 
M = M + 1 
@ARG 
D = M 
@SP 
A = M 
M = D 
@SP 
M = M + 1 
@THIS 
D = M 
@SP 
A = M 
M = D 
@SP 
M = M + 1 
@THAT 
D = M 
@SP 
A = M 
M = D 
@SP 
M = M + 1 
@7 
D = A 
@SP 
D = D - M 
D = -D 
@ARG 
M = D 
@SP 
D = M 
@LCL 
M = D 
// ------------------------------   goto Class2.set   ------------------------------
@Class2.set
0 ; JMP
// ------------------------------   label RETURN2.Class2.set   ------------------------------
(RETURN2.Class2.set)
// ------------------------------   pop temp 0   ------------------------------
@5 
D = A 
@addr 
M = D 
@SP 
M = M - 1 
@SP 
A = M 
D = M 
@addr 
A = M 
M = D 
// ------------------------------   call Class1.get 0   ------------------------------
@RETURN3.Class1.get 
D = A 
@SP 
A = M 
M = D 
@SP 
M = M + 1 
@LCL 
D = M 
@SP 
A = M 
M = D 
@SP 
M = M + 1 
@ARG 
D = M 
@SP 
A = M 
M = D 
@SP 
M = M + 1 
@THIS 
D = M 
@SP 
A = M 
M = D 
@SP 
M = M + 1 
@THAT 
D = M 
@SP 
A = M 
M = D 
@SP 
M = M + 1 
@5 
D = A 
@SP 
D = D - M 
D = -D 
@ARG 
M = D 
@SP 
D = M 
@LCL 
M = D 
// ------------------------------   goto Class1.get   ------------------------------
@Class1.get
0 ; JMP
// ------------------------------   label RETURN3.Class1.get   ------------------------------
(RETURN3.Class1.get)
// ------------------------------   call Class2.get 0   ------------------------------
@RETURN4.Class2.get 
D = A 
@SP 
A = M 
M = D 
@SP 
M = M + 1 
@LCL 
D = M 
@SP 
A = M 
M = D 
@SP 
M = M + 1 
@ARG 
D = M 
@SP 
A = M 
M = D 
@SP 
M = M + 1 
@THIS 
D = M 
@SP 
A = M 
M = D 
@SP 
M = M + 1 
@THAT 
D = M 
@SP 
A = M 
M = D 
@SP 
M = M + 1 
@5 
D = A 
@SP 
D = D - M 
D = -D 
@ARG 
M = D 
@SP 
D = M 
@LCL 
M = D 
// ------------------------------   goto Class2.get   ------------------------------
@Class2.get
0 ; JMP
// ------------------------------   label RETURN4.Class2.get   ------------------------------
(RETURN4.Class2.get)
// ------------------------------   label Sys.init.WHILE   ------------------------------
(Sys.init.WHILE)
// ------------------------------   goto Sys.init.WHILE   ------------------------------
@Sys.init.WHILE
0 ; JMP
