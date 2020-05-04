extern _GLOBAL_OFFSET_TABLE_                                ;for PIC
section .data
  a dq 0.5                                                  ;radical term
section .text
global f2:function
f2:
  push ebp
  mov ebp, esp 
  finit
  push ebx

  push ebx
  call .get_GOT

.get_GOT:
  pop ebx
  add ebx, _GLOBAL_OFFSET_TABLE_+$$-.get_GOT wrt ..gotpc

  fld qword[ebp+8]                                          ;x
  
  lea eax, [ebx+a wrt ..gotoff]
  fadd qword[eax]                                           ;x+0.5 in ST0
  fsqrt                                                     ;sqrt(x+0.5) in ST0
  
  pop ebx
  leave
  ret

