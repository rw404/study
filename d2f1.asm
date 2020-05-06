extern _GLOBAL_OFFSET_TABLE_                                ;for PIC
section .text
global d2f1:function
d2f1:
	push	ebp
	mov	ebp, esp
  push ebx
  sub esp, 8

  push ebx
  call .get_GOT

.get_GOT:
  pop ebx
  add ebx, _GLOBAL_OFFSET_TABLE_+$$-.get_GOT wrt ..gotpc

	fld	qword[ebp+8]                                          ;x in ST0
	fld1                                                      ;1 in ST0; x in ST1
	fsubp                                                     ;x-1 in ST1; pop x; x-1 in ST0
	
  fld	qword[ebp+8]                                          ;repeat steps 13-15
	fld1
	fsubp	
	
  fmulp                                                     ;(x-1)^2 in ST1; pop x-1; (x-1)^2 in ST0
	fld1                                                      ;1 in ST0;
	faddp	                                                    ;(x-1)^2 + 1 in ST1; pop 1; (x-1)^2 + 1 in ST0

  fld	qword[ebp+8]                                          ;repeat steps 13-23
	fld1                                                      
	fsubp                                                     
	
  fld	qword[ebp+8]                                          
	fld1
	fsubp	
	
  fmulp                                                     
	fld1                                                     
	faddp	                                                    ;------------------------

  fmulp                                                     ;((x-1)^2 + 1)^2 in ST1; pop (x-1)^2 + 1; ((x-1)^2 + 1)^2 in ST0 
  
  fld1                                                      ;1 in ST0; ((x-1)^2 + 1)^2 in ST1
  fld1                                                      ;1 in ST0 and in ST1; ((x-1)^2 + 1)^2 in ST2
  faddp                                                     ;2 in ST1; ((x-1)^2 + 1)^2 in ST2; pop 1; 2 in ST0; ((x-1)^2 + 1)^2 in ST1
  
  fld1                                                      ;repeat steps 40-41
  faddp
                                                            ;3 in ST0; ((x-1)^2 + 1)^2 in ST1 
	fdivrp                                                    ;ST1 = ST0/ST1; pop ST0; 3/((x-1)^2 + 1)^2 in ST0 
	
  fst qword[esp]                                            ;3/((x-1)^2 + 1)^2 saved in [esp]
  fld qword[esp]
  fld1                                                      ;
  fld1                                                      ;
  faddp                                                     ;2 in ST0; [esp] in ST1; previous result in ST2
  fmulp                                                     ;previous result in ST1; 6/((x-1)^2 + 1)^2 in ST0
  fstp qword[esp]                                           ;6/((x-1)^2 + 1)^2 in [esp]; previous result in ST0

  fld qword[ebp+8]                                          ;x in ST0; 3/((x-1)^2 + 1)^2 in ST1
  fld1                                                      ;1 in ST0; x in ST1; 3/((x-1)^2 + 1)^2 in ST2
  fsubp                                                     ;x-1 in ST1; 3/((x-1)^2 + 1)^2 in ST2; pop 1; x-1 in ST0; 3/((x-1)^2 + 1)^2 in ST1  
  fmulp                                                     ;3(x-1)/((x-1)^2 +1)^2 in ST1; pop x-1; 3(x-1)/((x-1)^2 +1)^2 in ST0 
  
  fld1                                                      ;1 in ST0; 3(x-1)/((x-1)^2 +1)^2 in ST1
  fld1                                                      ;1 in ST0 and in ST1; 3(x-1)/((x-1)^2 +1)^2 in ST2
  faddp                                                     ;2 in ST1; 3(x-1)/((x-1)^2 +1)^2 in ST2; pop 1; 2 in ST0; 3(x-1)/((x-1)^2 +1)^2 in ST1
  fmulp                                                     ;6/((x-1)^2 + 1)^2 in ST1; pop 2; 6(x-1)/((x-1)^2 +1)^2 in ST0
  
  fld1
  fld1
  faddp
  fld1
  faddp
  fld1
  faddp
  fmulp                                                     ;24(x-1)/((x-1)^2 + 1)^2 in ST0

  fld qword[ebp+8]
  fld1
  fsubp
  fmulp                                                     ;24(x-1)^2/((x-1)^2 + 1)^2 in ST0

  fld qword[ebp+8]
  fld1
  fsubp
  
  fld qword[ebp+8]
  fld1
  fsubp

  fmulp                                                     
  fld1
  faddp                                                     ;((x-1)^2 + 1) in ST0; 24(x-1)^2/((x-1)^2 + 1)^2 in ST1
  fdivp                                                     ;24(x-1)^2/((x-1)^2 + 1)^3 in ST0

  fsub qword[esp]                                           ;24(x-1)^2/((x-1)^2 + 1)^3 - 6/((x-1)^2 + 1)^2 in ST0

  
  add esp, 8
  pop ebx
  leave
  ret
