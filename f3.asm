extern _GLOBAL_OFFSET_TABLE_                                ;for PIC
section .data
  del dq 2.0                                                ;using in loop to mult [helper]
  helper dq 1.0                                             ;2^[-x]; [-x] - whole part of -x
section .text
global f3:function
f3:
  push ebp
  mov ebp, esp
  sub esp, 8
  push ebx
  
  push ebx
  call .get_GOT

.get_GOT:
  pop ebx 
  add ebx, _GLOBAL_OFFSET_TABLE_+$$-.get_GOT wrt ..gotpc    ;get GOT in ebx

  mov ecx, 0                                                ;flag of x's sign
  finit

  fld qword[ebp+8]                                          ;x
 
  fchs                                                      ;-x
  fldl2e                                                    ;log2 e
  fmulp                                                     ;log2 e^-x; pop log2 e
 
  fstp qword[esp]                                           ;result in [esp]; stack is empty

  mov edx, 1                                                ;prepare for x's sign changing 
  
  fldz                                                      ;zero in ST0
  fld qword[esp]                                            ;log2 e^-x in ST0; zero in ST1
  fucomip st1                                               ;ST0 vs ST1; pop [esp]
 
  cmovc ecx, edx                                            ;if st0<0 flag = 1
  
  fstp                                                      ;stack is empty  
  fld qword[esp]       
  fabs                                                      ;|log2 e^-x|

.L1:                                                        ;LOOP: while(|log2 e^-x|>1) [helper] *= 2, |log2 e^-x|--;
  
  fstp qword[esp]                                           ;result in [esp]; stack is empty
  fld1                                                      ;1 in ST0
  fld qword[esp]                                            ;[esp] in ST0; 1 in ST1

  fucomip st1                                               ;ST0 vs ST1; pop [esp]
  fstp                                                      ;pop 1 from stack; stack is empty
  fld qword[esp]                                            ;[esp] in ST0

  jbe .result wrt ..gotoff                                  ;if [esp] <= 1 jump to result
  
  lea eax, [ebx+helper wrt ..gotoff]
  fld qword[eax]                                            ;else [helper] in ST0
  lea eax, [ebx+del wrt ..gotoff]
  fmul qword[eax]                                           ;[helper] * 2 in ST0
  lea eax, [ebx+helper wrt ..gotoff]
  fstp qword[eax]                                           ;pop [helper]*2 in [helper]
  
  fld1                                                      ;[esp]--
  fsubp 

  jmp .L1 wrt ..gotoff

.result:                                                    ;if (log2 e^-x < 0) [helper] = 1/[helper]
  cmp ecx, 1 
  
  jb .end wrt ..gotoff                                      ;else jump to .end
  
  fld1                                                      ;1 in ST0
  lea eax, [ebx+helper wrt ..gotoff]
  fld qword[eax]                                            ;[helper] in ST0; 1 in ST1
  fdivp                                                     ;1/[helper] in ST1; pop [helper]; 1/[helper] in ST0 
  fstp qword[eax]                                           ;pop 1/[helper] in [helper]

  fchs                                                      ;ST0 = [esp]* -1; result after loop
 
.end:                                                       ;answer is 2^[esp] * 2^k, 2^k = [helper], k+[esp]=log2 e^-x

  f2xm1                                                     ;-1 <= ST0 <= 1; ST0 = 2^[esp] - 1
  fld1                                                      ;1 in ST0; 2^[esp]-1 in ST1

  faddp                                                     ;ST0++; 2^[esp] in ST0
  
  lea eax, [ebx+helper wrt ..gotoff]
  fmul qword[eax]                                           ;ST0 = [helper] * ST0 = e^-x
  
  pop ebx 
  leave 
  ret
  
  
