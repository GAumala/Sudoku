#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

#include "ClockUtils.h"
#include "ClockPuzzle.h"

uint8_t max(uint8_t a, uint8_t b){
	return a > b? a : b;
}

uint8_t evaluateSolution(uint8_t *per, uint8_t *clock, uint8_t length){
	for (uint8_t i = 0; i < length - 1; i++){
		if ((per[(i + 1) % length] != getValidIndex(length, per[i] + clock[per[i]]))
			&& (per[(i + 1) % length] != getValidIndex(length, per[i] - clock[per[i]]))){
			return 0;
		}
	}
	return 1;
}

void swap(uint8_t *x, uint8_t *y){
	uint8_t temp;
	temp = *x;
	*x = *y;
	*y = temp;
}


void permute(uint8_t *tmp, uint8_t l, uint8_t r, uint8_t *clock, uint8_t length){
	uint8_t i;
	if (l == r){
		if (evaluateSolution(tmp, clock, length)){
			//tmp es la solucion
			printClock(tmp, length);
			exit(0); //solo nos interesa la prinera solucion. abortar
		}
	} else {
		for (i = l; i <= r; i++) {
			swap((tmp + l), (tmp + i));
			permute(tmp, l + 1, r, clock, length);
			swap((tmp + l), (tmp + i));
		}
	}
}

void displayArgumentError(){
    printf("ERROR: No -i flag found\n");
    exit(1);
}

uint8_t main(int argc, char * argv[])
{
	if(argc > 2){
        int startIndex = getInputStartIndex(argc, argv);
        if(startIndex == -1){
            displayArgumentError();
        }
        uint8_t length = argc - startIndex;
        uint8_t *clock = parseClockFromArguments(argc, argv, startIndex, length);
		uint8_t *tmp = clockCpy(clock, length);
		permute(tmp, 0, length - 1, clock, length);
	} else {
		printf("Please pass a clock as argument using -i flag\n");
	}
	//uint8_t clock[] = { 6, 5, 1, 4, 2, 1, 6, 4, 2, 1, 5, 2 };
	/*
	Soluciones
	3,7,11,9,8,10,5,4,2,1,6,0
	3,7,11,9,10,5,4,2,1,8,6,0
	7,3,11,9,8,10,5,4,2,1,6,0
	7,3,11,9,10,5,4,2,1,8,6,0
	9,8,10,5,4,2,3,7,11,1,6,0
	9,10,5,4,2,3,7,11,1,8,6,0
	*/
	return 1;
}
