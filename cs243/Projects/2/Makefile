all: mrEd testdllist

mrEd: mrEd.c dlList.c dlList.h
	gcc -o mrEd mrEd.c dlList.c dlList.h

testdllist: testdllist.c dlList.c dlList.h
	gcc -o testdllist testdllist.c dlList.c dlList.h

clean:
	rm -f *.o mrEd testdllist