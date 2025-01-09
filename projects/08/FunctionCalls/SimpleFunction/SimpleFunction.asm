
// **************************************    SimpleFunction.vm code started!    **************************************

// ------------------------------   function SimpleFunction.test 2   ------------------------------
(SimpleFunction.test) 
@SP 
A = M 
M = 0 
@SP 
M = M + 1 
@SP 
A = M 
M = 0 
@SP 
M = M + 1 
// ------------------------------   push local 0   ------------------------------
@LCL 
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
// ------------------------------   push local 1   ------------------------------
@LCL 
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
// ------------------------------   not   ------------------------------
@SP 
M = M - 1 
A = M 
D = M 
M = !D 
@SP 
M = M + 1 
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
(END) 
@END 
0 ; JMP 
