all: test

test: f1.o deb.o
			gcc -o test f1.o deb.o -m32
f1.o: f1.asm
			nasm -f elf32 f1.asm
deb.o: deb.c
			gcc -c -o deb.o deb.c -m32
clean: test f1.o deb.o
			rm -f test f1.o deb.o

