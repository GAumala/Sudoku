all: main

GLIB = `pkg-config --cflags --libs glib-2.0`
JSONLIB = `pkg-config --cflags --libs json-c`
C99 = -std=gnu99
DEBUG = -g

SearchTreeNode.o: SearchTreeNode.c
	gcc -c $(DEBUG) $(C99) SearchTreeNode.c $(GLIB) -o SearchTreeNode.o

ClockPuzzle.o: ClockPuzzle.c
	gcc -c $(DEBUG) $(C99)  ClockPuzzle.c $(GLIB) $(JSONLIB) -o ClockPuzzle.o

cmdclock.o: cmdclock.c
	gcc -c $(C99) cmdclock.c -o cmdclock.o

main: ClockPuzzle.o SearchTreeNode.o cmdclock.o main.c
	gcc $(DEBUG) $(C99) ClockPuzzle.o SearchTreeNode.o cmdclock.o main.c $(GLIB) $(JSONLIB) -o main

brute: cmdclock.o BruteForce.c
	gcc $(DEBUG) $(C99) cmdclock.o BruteForce.c -o brute

test: ClockPuzzle.o SearchTreeNode.o test.c
	gcc $(DEBUG) $(C99) ClockPuzzle.o SearchTreeNode.o test.c $(GLIB) $(JSONLIB) -o test

clean:
	rm *.o main test
