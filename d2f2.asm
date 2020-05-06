extern _GLOBAL_OFFSET_TABLE_                                ;for PIC
section .data
  a dq 0.5                                                  ;radical term
section .text
global d2f2:function
d2f2:
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

  fld qword[ebp+8]
  fadd qword[eax]
  fmulp                                                     ;(x+0.5)^2 in ST0

  fld qword[ebp+8]
  fadd qword[eax]
  fmulp                                                     ;(x+0.5)^3 in ST0

  fsqrt                                                     ;sqrt((x+0.5)^3) in ST0

  fld1                                                      ;1 in ST0; sqrt((x+0.5)^3) in ST1
  fdivrp                                                    ;ST1 = ST0/ST1; 1/sqrt((x+0.5)^3) in ST1; pop 1; 1/sqrt((x+0.5)^3) in ST0
  fmul qword[eax]                                           ;1/(2*sqrt((x+0.5)^3)) in ST0
  fmul qword[eax]                                           ;1/(4*sqrt((x+0.5)^3)) in ST0
  fchs                                                      ;-1/(4*sqrt((x+0.5)^3)) in ST0

  pop ebx
  leave
  ret

