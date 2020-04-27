extern printf
section .data
  a dq 3.0
  b dq 1.0
section .rodata
  lc0 db "%f", 0
section .text
global f1
f1:
  push ebp
  mov ebp, esp
  sub esp, 8 
  
  finit 
  fld qword[ebp+8] 
  
  fld qword[b]
  fsubp
  
  fst qword[esp]

  fmul qword[esp]

  fld qword[b]
  faddp

  fstp qword[esp]
  fld qword[a]
  
  fdiv qword[esp]
 
  leave
  ret 
  
