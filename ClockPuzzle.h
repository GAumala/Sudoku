#ifndef CLOCKPUZZLE
#define CLOCKPUZZLE

#include <glib-2.0/glib.h>
#include "SearchTreeNode.h"

/**
* En este header file estan las funciones para solucionar el problema
* del clock puzzle
*/
void generarHijos(uint8_t clock[], uint8_t clockSize, SearchTreeNode *node);

void printClock(uint8_t clock[], uint8_t clockSize);

GArray *getCurrentPath(SearchTreeNode *node);

void printPath(GArray *path, uint8_t clock[]);

GArray *findAllClockSolutions(uint8_t clock[], int clockSize, int verbose);

#endif
