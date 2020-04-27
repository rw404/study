section .data
  a dq 0.5
section .text
global f2
f2:
  push ebp
  mov ebp, esp
  finit
  sub esp, 8
  fld qword[ebp+8]
  fsub qword[a]
  fsqrt

  leave
  ret

