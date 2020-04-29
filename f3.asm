extern printf
section .data
  a dq -1.0
  del dq 2.0
  helper dq 1.0
  flag dq 0.0
section .rodata
  LC0 db "%f", 0
section .text
global f3
f3:
  push ebp
  mov ebp, esp
  sub esp, 16
  and esp, 0xfffffff0
  mov eax, 0
  finit

  fld qword[ebp+8];ebp+8 x
  ;fst qword[esp+4]
  ;mov dword[esp], LC0
  ;call printf

  fmul qword[a];-x
  fldl2e;log2 e
  fmulp; log2 e^-x
  ;fld1
  ;fsubp; qword[helper]
  ;fst qword[esp+4]
  ;mov dword[esp], LC0
  ;call printf

  fstp qword[esp]
  ;mov dword[esp], LC0
  ;call printf
  fld qword[flag];ST1
  fld qword[esp];ST0
  fucomip st1;st0 vs st1

  jnc .dontchangeflag;if st0>=0
  fld qword[helper]
  ;fst qword[esp+4]
  fstp qword[flag]
  ;mov dword[esp], LC0
  ;call printf
  mov eax, 1
  
.dontchangeflag:
  ;fstp
  fld qword[esp]
  fabs
  ;fld qword[flag]
  ;fst qword[esp+4]
  ;mov dword[esp], LC0
  ;call printf

.L1:
  
  fstp qword[esp]
  fld1; ST1
  fld qword[esp]; ST0

  fucomip st1;ST0 vs ST1
  fstp
  fld qword[esp]
  ;fld qword[esp]
  ;fst qword[esp+4]
  ;mov dword[esp], LC0
  ;call printf


  jbe .result
  
  fld qword[helper]
  fmul qword[del]
  ;fst qword[esp+4]
  ;mov dword[esp], LC0
  ;call printf


  fstp qword[helper]
  
  fld1

  fsubp
  ;fst qword[esp+4]
  ;mov dword[esp], LC0
  ;call printf

  jmp .L1

.result:
  ;fst qword[esp+4]
  ;mov dword[esp], LC0
  ;call printf
  ;fld qword[flag]
  ;fld1;ST1
  ;fld qword[flag]
  ;fstp qword[esp+4]
  ;mov dword[esp], LC0
  ;call printf
  cmp eax, 1
  jb .end
  
;  fucomip st1
;  fstp
;  jb .hthanzero
;  fstp

  fld1
  fld qword[helper]
  ;fst qword[esp+4]
  ;mov dword[esp], LC0
  ;call printf

;Zdes' shpion!!!!!

  fdivp
  ;fst qword[esp+4]
  ;mov dword[esp], LC0
  ;call printf


  fstp qword[helper]
  fstp qword[esp]
  fld qword[esp]
  fmul qword[a]
;  jmp .end

;.hthanzero:
  ;fstp 
.end:
  ;fst qword[esp+4]
  ;mov dword[esp], LC0
  ;call printf

  f2xm1
  fld1

  faddp
  
  fmul qword[helper]

  leave 
  ret
  
  
