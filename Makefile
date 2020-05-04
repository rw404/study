OBJS = f1.o f2.o f3.o df1.o df2.o df3.o

all: programm
programm: deb.o libthreefuncs.so	
	      gcc -m32 -Xlinker -rpath='$$ORIGIN/' -o programm deb.o libthreefuncs.so 
libthreefuncs.so: f1.o f2.o f3.o df1.o df2.o df3.o
				gcc -m32 -shared -o libthreefuncs.so f1.o f2.o f3.o df1.o df2.o df3.o
f1.o: f1.asm
				nasm -f elf32 -o f1.o f1.asm
f2.o: f2.asm
				nasm -f elf32 -o f2.o f2.asm
f3.o: f3.asm
				nasm -f elf32 -o f3.o f3.asm
df1.o: df1.asm
				nasm -f elf32 -o df1.o df1.asm
df2.o: df2.asm
				nasm -f elf32 -o df2.o df2.asm
df3.o: df3.asm
				nasm -f elf32 -o df3.o df3.asm
deb.o: threefuncs.h deb.c
				gcc -c -o deb.o deb.c -m32
clean: $(OBJS) programm
				rm -f $(OBJS) programm
