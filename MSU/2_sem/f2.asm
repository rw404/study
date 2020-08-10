extern _GLOBAL_OFFSET_TABLE_                                ;for PIC
section .data
  a dq 0.5                                                  ;radical term
section .text
global f2:function
f2:
  push ebp
  mov ebp, esp 
  push ebx

  call .get_GOT

.get_GOT:
  pop ebx
  add ebx, _GLOBAL_OFFSET_TABLE_+$$-.get_GOT wrt ..gotpc
  
  finit

  fld qword[ebp+8]                                          ;x
  
  lea eax, [ebx+a wrt ..gotoff]
  fadd qword[eax]                                           ;x+0.5 in ST0
  fsqrt                                                     ;sqrt(x+0.5) in ST0
  
  mov ebx, [ebp-4]                                          ;ebx is restored

  leave
  ret

