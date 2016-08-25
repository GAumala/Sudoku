all: main brute

GLIB = `pkg-config --cflags --libs glib-2.0`
JSONLIB = `pkg-config --cflags --libs json-c`
C99 = -std=gnu99
DEBUG = -g

SearchTreeNode.o: SearchTreeNode.c
	gcc -c $(DEBUG) $(C99) SearchTreeNode.c $(GLIB) -o SearchTreeNode.o

ClockPuzzle.o: ClockPuzzle.c
	gcc -c $(DEBUG) $(C99)  ClockPuzzle.c $(GLIB) $(JSONLIB) -o ClockPuzzle.o

ClockUtils.o: ClockUtils.c
	gcc -c $(C99) ClockUtils.c -o ClockUtils.o

main: ClockPuzzle.o SearchTreeNode.o ClockUtils.o main.c
	gcc $(DEBUG) $(C99) ClockPuzzle.o SearchTreeNode.o ClockUtils.o main.c $(GLIB) $(JSONLIB) -o main

brute: ClockUtils.o BruteForce.c
	gcc $(DEBUG) $(C99) ClockUtils.o BruteForce.c $(GLIB) $(JSONLIB) -o brute

test: ClockPuzzle.o SearchTreeNode.o test.c
	gcc $(DEBUG) $(C99) ClockPuzzle.o SearchTreeNode.o test.c $(GLIB) $(JSONLIB) -o test

clean:
	rm *.o main brute
