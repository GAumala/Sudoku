all: main

GLIB = `pkg-config --cflags --libs glib-2.0`
C99 = -std=gnu99

SearchTreeNode.o: SearchTreeNode.c
	gcc -c $(C99) SearchTreeNode.c $(GLIB) -o SearchTreeNode.o

ClockPuzzle.o: ClockPuzzle.c
	gcc -c $(C99)  ClockPuzzle.c $(GLIB) -o ClockPuzzle.o

main: ClockPuzzle.o SearchTreeNode.o main.c
	gcc $(C99) ClockPuzzle.o SearchTreeNode.o main.c $(GLIB) -o main

test: ClockPuzzle.o SearchTreeNode.o test.c
	gcc $(C99) ClockPuzzle.o SearchTreeNode.o test.c $(GLIB) -o test

clean:
	rm *.o main test
