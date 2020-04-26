extern _printf
section .data
  a dd 3.0
  b dd 1.0
section .rodata
  lc0 db "%f", 0
section .text
global _main
_main:
  push ebp
  mov ebp, esp
  sub esp, 12
  and esp, 0xfffffff0
  finit
  ;3/((x-1)^2 + 1) 
  fld dword[ebp+8]
  fld dword[b]
  fsubp
  fst dword[esp]
  fmul dword[esp]
  fld dword[b]
  faddp
  fstp dword[esp]
  fld dword[a]
  fdiv dword[esp]
  fstp qword[esp+ 4]
 
  mov dword[esp], lc0
  call _printf  
 
  leave
  ret 
  
