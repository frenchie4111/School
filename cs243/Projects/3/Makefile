all: mish
	
mish: mish.o dll_mike.o
	gcc -ggdb -std=c99 -Wall -o mish mish.o dll_mike.o

mish.o: mish.c
	gcc -ggdb -std=c99 -Wall -c mish.c -o mish.o
	
dll_mike.o: dll_mike.c dll_mike.h
	gcc -ggdb -std=c99 -Wall -c dll_mike.c -o dll_mike.o