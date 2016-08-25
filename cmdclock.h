#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int getInputStartIndex(int argc, char *argv[]);

uint8_t *parseClockFromArguments(int argc, char *argv[], int startIndex, uint8_t clockSize);
