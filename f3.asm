extern _GLOBAL_OFFSET_TABLE_
extern __x86.get_pc_thunk.bx
section .data
  a dq -1.0            ;to neg elements
  del dq 2.0           ;using in loop to mult [helper]
  helper dq 1.0        ;2^[-x]; [-x] - whole part of -x
  flag dq 0.0          ;to cmp -x with zero
section .text
global f3:function
f3:
  push ebp
  mov ebp, esp
  sub esp, 8
  push ebx
 
  call .get_GOT

.get_GOT:
  pop ebx 
  add ebx, _GLOBAL_OFFSET_TABLE_+$$-.get_GOT wrt ..gotpc

  mov ecx, 0           ;flag of x's sign
  finit

  fld qword[ebp+8]     ;x
  
  lea eax, [ebx+a wrt ..gotoff]
  fmul qword[eax]        ;-x
  fldl2e               ;log2 e
  fmulp                ;log2 e^-x; pop log2 e
 
  fstp qword[esp]      ;result in [esp]; stack is empty
  
  lea eax, [ebx+flag wrt ..gotoff]
  fld qword[eax]      ;ST1
  fld qword[esp]       ;ST0
  fucomip st1          ;ST0 vs ST1; pop [esp]
  
  lea eax, [ebx+.dontchangeflag wrt ..gotoff]
  jnc .dontchangeflag wrt ..gotoff ;if st0>=0 -> don't change
 
  mov ecx, 1           ;if st0<0 flag = 1
  
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

  lea eax, [ebx+.result wrt ..gotoff]
  jbe .result wrt ..gotoff         ;if [esp] <= 1 jump to result
  
  lea eax, [ebx+helper wrt ..gotoff]
  fld qword[eax]       ;else
  lea eax, [ebx+del wrt ..gotoff]
  fmul qword[eax]      ;[helper] = [helper] * 2
  
  lea eax, [ebx+helper wrt ..gotoff]
  fstp qword[eax]
  
  fld1                 ;ST1  = [esp]-1

  fsubp 

  lea eax, [ebx+.L1 wrt ..gotoff]
  jmp .L1 wrt ..gotoff

.result:
  cmp ecx, 1 
  
  jb .end wrt ..gotoff              ;if log2 e^-x >= 0 jump to .end
  
  fld1                 ;else [helper] = 1/[helper]
  lea eax, [ebx+helper wrt ..gotoff]
  fld qword[eax]
  fdivp 
  fstp qword[eax]

  lea eax, [ebx+a wrt ..gotoff]
  fmul qword[eax]        ;ST0 = [esp]* -1; result after loop
 
.end:

  f2xm1                ;-1 <= ST0 <= 1; ST0 = 2^ST0 - 1
  fld1

  faddp                ;ST0++; in ST0 2^result_after_loop
  
  lea eax, [ebx+helper wrt ..gotoff]
  fmul qword[eax]   ;ST0 = [helper] * ST0 = e^-x 
  
  pop ebx
  leave 
  ret
  
  
