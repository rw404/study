OBJS = f1.o f2.o f3.o df1.o df2.o df3.o d2f1.o d2f2.o d2f3.o

all: programm
programm: deb.o libthreefuncs.so	
	      gcc -m32 -Xlinker -rpath='$$ORIGIN/' -o programm deb.o libthreefuncs.so -lm 
libthreefuncs.so: $(OBJS)
				gcc -m32 -shared -o libthreefuncs.so $(OBJS)
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
d2f1.o: d2f1.asm
				nasm -f elf32 -o d2f1.o d2f1.asm
d2f2.o: d2f2.asm
				nasm -f elf32 -o d2f2.o d2f2.asm
d2f3.o: d2f3.asm
				nasm -f elf32 -o d2f3.o d2f3.asm
deb.o: threefuncs.h deb.c
				gcc -c -o deb.o deb.c -m32
clean: $(OBJS) programm deb.o
				rm -f $(OBJS) programm deb.o
