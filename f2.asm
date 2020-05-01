section .data
  a dq 0.5             ;radical term
section .text
global f2
f2:
  push ebp
  mov ebp, esp
  sub esp, 8
  finit

  fld qword[ebp+8]     ;x
  fadd qword[a]        ;x+0.5
  fsqrt                ;sqrt(x+0.5)

  leave
  ret

