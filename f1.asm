section .data
  a dq 3.0             ;numerator
section .text
global f1
f1:
  push ebp
  mov ebp, esp
  sub esp, 8 
  
  finit 
  fld qword[ebp+8]     ;x
  
  fld1
  fsubp                ;x-1
  
  fst qword[esp]

  fmul qword[esp]      ;(x-1)^2

  fld1
  faddp                ;(x-1)^2 +1

  fstp qword[esp]      ;result in [esp]; stack is empty
  fld qword[a]         ;numerator
  
  fdiv qword[esp]      ;result
 
  leave
  ret 
  
