section .data
  a dq -1.0
  del dq 2.0
  helper dq 1.0
  flag dq 0.0
section .text
global f3
f3:
  push ebp
  mov ebp, esp
  sub esp, 8
  finit

  fld qword[ebp+8];x
  fmul qword[a];-x
  fldl2e;log2 e
  fmulp; log2 e^-x

  fstp qword[esp]

  fld qword[flag]
  
  fcomip

  jge .dontchangeflag
  mov qword[flag], 1.0  

.dontchangeflag:

  fabs
.L1:
  
  fld1

  fcomip

  jbe .result
  
  fld qword[helper]
  fmul qword[del]
  fstp qword[helper]

  fld1

  fsubp
  jmp .L1

.result:
  
  fld qword[flag]
  fld1

  fcomip

  jb .hthanzero
  fstp

  fld1
  fld qword[helper]

  fdivp
  fstp qword[helper]

  jmp .result

.hthanzero:
  fstp 

.result:

  f2xm1
  fld1

  faddp
  
  fmul qword[helper]

  leave 
  ret
  
  
