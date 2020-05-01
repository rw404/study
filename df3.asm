section .data
  a dq -1.0            ;to neg elements
  del dq 2.0           ;using in loop to mult [helper]
  helper dq 1.0        ;2^[-x]; [-x] - whole part of -x
  flag dq 0.0          ;to cmp -x with zero
section .text
global df3
df3:
  push ebp
  mov ebp, esp
  sub esp, 16
  and esp, 0xfffffff0
  mov eax, 0           ;flag of x's sign
  finit

  fld qword[ebp+8]     ;x
  
  fmul qword[a]        ;-x
  fldl2e               ;log2 e
  fmulp                ;log2 e^-x; pop log2 e
 
  fstp qword[esp]      ;result in [esp]; stack is empty
  
 
  fld qword[flag]      ;ST1
  fld qword[esp]       ;ST0
  fucomip st1          ;ST0 vs ST1; pop [esp]

  jnc .dontchangeflag  ;if st0>=0 -> don't change
 
  mov eax, 1           ;if st0<0 flag = 1
  
.dontchangeflag:
  fstp                 ;stack is empty  
  fld qword[esp]       
  fabs                 ;|log2 e^-x|

.L1:
  
  fstp qword[esp]      ;result in [esp]
  fld1                 ;ST1
  fld qword[esp]       ;ST0

  fucomip st1          ;ST0 vs ST1; pop [esp]
  fstp                 ;pop 1 from stack; stack is empty
  fld qword[esp]

  jbe .result          ;if [esp] <= 1 jump to result
  
  fld qword[helper]    ;else
  fmul qword[del]      ;[helper] = [helper] * 2

  fstp qword[helper]
  
  fld1                 ;ST1  = [esp]-1

  fsubp 

  jmp .L1

.result:
  cmp eax, 1 
  jb .end              ;if log2 e^-x >= 0 jump to .end
  
  fld1                 ;else [helper] = 1/[helper]
  fld qword[helper]
  fdivp 
  fstp qword[helper]

  fmul qword[a]        ;ST0 = [esp]* -1; result after loop
 
.end:

  f2xm1                ;-1 <= ST0 <= 1; ST0 = 2^ST0 - 1
  fld1

  faddp                ;ST0++; in ST0 2^result_after_loop
  
  fmul qword[helper]   ;ST0 = [helper] * ST0 = e^-x

  fmul qword[a]        ;ST0 = -e^-x

  leave 
  ret
  
  
