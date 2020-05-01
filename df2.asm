section .data
  a dq 0.5             ;radical term
section .text
global df2
df2:
  push ebp
  mov ebp, esp
  sub esp, 8
  finit

  fld qword[ebp+8]     ;x
  fadd qword[a]        ;x+0.5
  fsqrt                ;sqrt(x+0.5)

  fstp qword[esp]      ;result in [esp]
  fld1
  fdiv qword[esp]      ;1/sqrt(x+0.5)
  fmul qword[a]        ;1/2*sqrt(x+0.5)

  leave
  ret

