#include <stdint.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int getInputStartIndex(int argc, char *argv[]);

uint8_t *parseClockFromArguments(int argc, char *argv[], int startIndex, uint8_t clockSize);

void printClock(uint8_t clock[], uint8_t clockSize);

uint8_t getValidIndex(uint8_t clockSize, int16_t rawIndex);

uint8_t* clockCpy(uint8_t *clock, uint8_t length);
