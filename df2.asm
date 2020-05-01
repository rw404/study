section .data
  a dq 0.5
section .text
global df2
df2:
  push ebp
  mov ebp, esp
  finit
  sub esp, 8
  fld qword[ebp+8]
  fsub qword[a]
  fsqrt

  fstp qword[esp]
  fld1
  fdiv qword[esp]
  fmul qword[a]

  leave
  ret

