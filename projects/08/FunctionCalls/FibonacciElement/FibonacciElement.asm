// ####################################       Program Initialization  ####################################       
@256 
D = A 
@SP 
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

// **************************************    Main.vm code started!    **************************************

// ------------------------------   function Main.fibonacci 0   ------------------------------
(Main.fibonacci) 
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
// ------------------------------   push constant 2   ------------------------------
@2 
D = A 
@SP 
A = M 
M = D 
@SP 
M = M + 1 
// ------------------------------   lt   ------------------------------
@SP 
M = M - 1 
A = M 
D = M 
@SP 
M = M - 1 
A = M 
D = D - M 
@TRUE0
D ; JGT 
D = 0 
@FALSE0
0 ; JMP 
(TRUE0) 
D = -1 
(FALSE0) 
@SP 
A = M 
M = D 
@SP 
M = M + 1 
// ------------------------------   if-goto Main.fibonacci.IF_TRUE   ------------------------------
@SP
M = M - 1 
A = M 
D = M 
@Main.fibonacci.IF_TRUE
D ; JNE
// ------------------------------   goto Main.fibonacci.IF_FALSE   ------------------------------
@Main.fibonacci.IF_FALSE
0 ; JMP
// ------------------------------   label Main.fibonacci.IF_TRUE   ------------------------------
(Main.fibonacci.IF_TRUE)
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
// ------------------------------   label Main.fibonacci.IF_FALSE   ------------------------------
(Main.fibonacci.IF_FALSE)
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
// ------------------------------   push constant 2   ------------------------------
@2 
D = A 
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
// ------------------------------   call Main.fibonacci 1   ------------------------------
@RETURN1.Main.fibonacci 
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
@6 
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
// ------------------------------   goto Main.fibonacci   ------------------------------
@Main.fibonacci
0 ; JMP
// ------------------------------   label RETURN1.Main.fibonacci   ------------------------------
(RETURN1.Main.fibonacci)
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
// ------------------------------   push constant 1   ------------------------------
@SP 
A = M 
M = 1 
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
// ------------------------------   call Main.fibonacci 1   ------------------------------
@RETURN2.Main.fibonacci 
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
@6 
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
// ------------------------------   goto Main.fibonacci   ------------------------------
@Main.fibonacci
0 ; JMP
// ------------------------------   label RETURN2.Main.fibonacci   ------------------------------
(RETURN2.Main.fibonacci)
// ------------------------------   add   ------------------------------
@SP 
M = M - 1 
A = M 
D = M 
@SP 
M = M - 1 
A = M 
D = D + M 
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
// ------------------------------   push constant 4   ------------------------------
@4 
D = A 
@SP 
A = M 
M = D 
@SP 
M = M + 1 
// ------------------------------   call Main.fibonacci 1   ------------------------------
@RETURN3.Main.fibonacci 
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
@6 
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
// ------------------------------   goto Main.fibonacci   ------------------------------
@Main.fibonacci
0 ; JMP
// ------------------------------   label RETURN3.Main.fibonacci   ------------------------------
(RETURN3.Main.fibonacci)
// ------------------------------   label Sys.init.WHILE   ------------------------------
(Sys.init.WHILE)
// ------------------------------   goto Sys.init.WHILE   ------------------------------
@Sys.init.WHILE
0 ; JMP
