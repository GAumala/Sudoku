all: main

GLIB = `pkg-config --cflags --libs glib-2.0`
JSONLIB = `pkg-config --cflags --libs json-c`
C99 = -std=gnu99
DEBUG = -g

SearchTreeNode.o: SearchTreeNode.c
	gcc -c $(DEBUG) $(C99) SearchTreeNode.c $(GLIB) -o SearchTreeNode.o

ClockPuzzle.o: ClockPuzzle.c
	gcc -c $(DEBUG) $(C99)  ClockPuzzle.c $(GLIB) $(JSONLIB) -o ClockPuzzle.o

main: ClockPuzzle.o SearchTreeNode.o main.c
	gcc $(DEBUG) $(C99) ClockPuzzle.o SearchTreeNode.o main.c $(GLIB) $(JSONLIB) -o main

test: ClockPuzzle.o SearchTreeNode.o test.c
	gcc $(DEBUG) $(C99) ClockPuzzle.o SearchTreeNode.o test.c $(GLIB) $(JSONLIB) -o test

clean:
	rm *.o main test
