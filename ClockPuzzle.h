#ifndef CLOCKPUZZLE
#define CLOCKPUZZLE

#include <glib-2.0/glib.h>
#include <json-c/json.h>
#include "SearchTreeNode.h"

/**
* En este header file estan las funciones para solucionar el problema
* del clock puzzle
*/

void generarHijos(uint8_t clock[], uint8_t clockSize, SearchTreeNode *node);

GArray *getCurrentPath(SearchTreeNode *node);

void printPath(GArray *path, uint8_t clock[]);

GArray *findClockSolution(uint8_t clock[], uint8_t clockSize,
    json_object *stateList, uint8_t startPosition);
/**
* Encuentra la prinera solucion de un reloj
* @param clock el reloj a resolver
* @param clokSize el tamanio del reloj
* @param stateList un json object donde guardar la lista de estados. El resultado
* es un array de arrays de posiciones. Si es null no hace nada
*/
GArray *findFirstClockSolution(uint8_t clock[], uint8_t clockSize,
    json_object *stateList);

GArray *findAllClockSolutions(uint8_t clock[], uint8_t clockSize, json_object *stateList);

#endif
