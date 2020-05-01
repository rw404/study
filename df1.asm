section .data
  a dq 3.0
  b dq -1.0
  c dq 2.0
section .text
global df1
df1:
  push ebp
  mov ebp, esp
  sub esp, 8 
  
  finit 
  fld qword[ebp+8] 
  
  fld1
  fsubp
  
  fst qword[esp]

  fmul qword[esp]

  fld1 
  faddp

  fstp qword[esp]
  fld qword[a]
  
  fdiv qword[esp]
  fdiv qword[esp]
  fld qword[ebp+8]
  fld1
  fsubp
  fmulp
  
  fmul qword[c]
  fmul qword[b]
 
  leave
  ret 
  
