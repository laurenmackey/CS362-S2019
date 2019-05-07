CFLAGS= -Wall -fpic -coverage -lm -std=c99

all: testme.c
	gcc -o testme -g testme.c $(CFLAGS)

clean:
	rm -f *.o testme *.gcov *.gcda *.gcno