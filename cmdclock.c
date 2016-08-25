#include "cmdclock.h"

int getInputStartIndex(int argc, char *argv[]){
    char *startFlag = "-i";
    for(int i = 0; i < argc; i++){
        if(strcmp(startFlag, argv[i]) == 0)
            return i + 1;
    }

    return -1;
}

uint8_t *parseClockFromArguments(int argc, char *argv[], int startIndex, uint8_t clockSize){
    uint8_t *clock = (uint8_t *) malloc(sizeof(uint8_t) * clockSize);
    for(int i = startIndex; i < argc; i++){
        clock[i - startIndex] = atoi(argv[i]);
    }
    return clock;
}
