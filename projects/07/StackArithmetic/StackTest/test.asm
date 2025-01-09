// push constant 71
@71 
D = A 
@SP 
A = M 
M = D 
@SP 
M = M + 1 
// neg
@SP 
M = M - 1 
A = M 
D = M 
M = -D 
@SP 
M = M + 1 
// pop static 0
@SP 
M = M - 1 
@SP 
A = M 
D = M 
@test.0 
M = D 
(END) 
@END 
0 ; JMP 
