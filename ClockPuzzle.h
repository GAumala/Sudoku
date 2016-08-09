#ifndef CLOCKPUZZLE
#define CLOCKPUZZLE

#include "SearchTreeNode.h"

/**
* En este header file estan las funciones para solucionar el problema
* del clock puzzle
*/
GArray *findAllClockSolutions(uint8_t clock[], int clockSize);

void generarHijos(uint8_t clock[], uint8_t clockSize, SearchTreeNode *node);

void printClock(uint8_t clock[], uint8_t clockSize);

#endif
