extern _GLOBAL_OFFSET_TABLE_                                ;for PIC
section .text
global f1:function
f1:
	push	ebp
	mov	ebp, esp
  push ebx

  call .get_GOT

.get_GOT:
  pop ebx
  add ebx, _GLOBAL_OFFSET_TABLE_+$$-.get_GOT wrt ..gotpc
	
  fld	qword[ebp+8]                                          ;x in ST0
	fld1                                                      ;1 in ST0; x in ST1
	fsubp                                                     ;x-1 in ST1; pop x; x-1 in ST0
	
  fld	qword[ebp+8]                                          ;repeat steps 12-15
	fld1
	fsubp	
	
  fmulp                                                     ;(x-1)^2 in ST1; pop x-1; (x-1)^2 in ST0
	fld1                                                      ;1 in ST0;
	faddp	                                                    ;(x-1)^2 + 1 in ST1; pop 1; (x-1)^2 + 1 in ST0
	
  fld1                                                      ;1 in ST0; (x-1)^2 + 1 in ST1
  fld1                                                      ;1 in ST0 and in ST1; (x-1)^2 + 1 in ST2
  faddp                                                     ;2 in ST1; (x-1)^2 + 1 in ST2; pop 1; 2 in ST0; (x-1)^2 + 1 in ST1 
  
  fld1                                                      ;repeat steps 26-27
  faddp
                                                            ;3 in ST0; (x-1)^2 + 1 in ST1 
	fdivrp                                                    ;ST1 = ST0/ST1; pop ST0; 3/((x-1)^2 + 1) 
	
  mov ebx, [ebp-4]                                          ;ebx is restored

  leave
  ret
