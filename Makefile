all: test

test: f3.o deb.o
			gcc -o test f3.o deb.o -m32
f3.o: f3.asm
			nasm -f elf32 f3.asm
deb.o: deb.c
			gcc -c -o deb.o deb.c -m32
clean: test f3.o deb.o
			rm -f test f3.o deb.o

