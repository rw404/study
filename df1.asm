section .data
  a dq 3.0             ;numerator
  b dq -1.0            ;multiplier
  c dq 2.0             ;multiplier
section .text
global df1
df1:
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

  fstp qword[esp]
  fld qword[a]
  
  fdiv qword[esp]      ;3/((x-1)^2 +1)
  fdiv qword[esp]      ;3/((x-1)^2 +1)^2 =:res1
  fld qword[ebp+8]     
  fld1
  fsubp                ;in ST0 x-1, in ST1 res1
  fmulp                ;3(x-1)/((x-1)^2 +1)^2
  
  fmul qword[c]
  fmul qword[b]        ;result is -6(x-1)/((x-1)^2 +1)^2
 
  leave
  ret 
  
