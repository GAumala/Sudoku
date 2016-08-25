#include "ClockUtils.h"

uint8_t getValidIndex(uint8_t clockSize, int16_t rawIndex){
    uint8_t res = rawIndex;
    if(rawIndex == 0 || ((uint8_t)rawIndex) == clockSize){
        return 0;
    }

    if(rawIndex < 0){
        int16_t clock16 = (int16_t) clockSize;
        res = (uint8_t)(clock16 + rawIndex);
    } else if(rawIndex > clockSize)
        res = rawIndex - clockSize;
    return res;
}

void printClock(uint8_t clock[], uint8_t clockSize){
    printf("[ %d", clock[0]);
    for(uint8_t i = 1; i < clockSize; i++)
        printf(", %d", clock[i]);
    printf(" ]\n");
}

int getInputStartIndex(int argc, char *argv[]){
    char *startFlag = "-i";
    for(int i = 0; i < argc; i++){
        if(strcmp(startFlag, argv[i]) == 0)
            return i + 1;
    }

    return -1;
}


uint8_t* clockCpy(uint8_t *clock, uint8_t length){
	uint8_t *new_array;
	new_array = (uint8_t*)malloc(sizeof(uint8_t)*length);

	for (uint8_t i = 0; i < length; i++){
		new_array[i] = i;
	}

	return new_array;
}

uint8_t *parseClockFromArguments(int argc, char *argv[], int startIndex, uint8_t clockSize){
    uint8_t *clock = (uint8_t *) malloc(sizeof(uint8_t) * clockSize);
    for(int i = startIndex; i < argc; i++){
        clock[i - startIndex] = atoi(argv[i]);
    }
    return clock;
}
