#ifndef SEARCHTREENODE
#define SEARCHTREENODE

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <glib-2.0/glib.h>

/**
* Esta es la estructura para el arbol de busqueda binaria
*/

typedef struct SearchTreeNode {
   struct SearchTreeNode *leftChild;
   struct SearchTreeNode *rightChild;
   struct SearchTreeNode *parent;
   void *content;
   int isDeadEnd;
} SearchTreeNode;


SearchTreeNode *newSearchTreeNode(SearchTreeNode *parent, void *content);

void generarHijos(uint8_t clock[], uint8_t clockSize, SearchTreeNode *node);

SearchTreeNode *getNextNode(SearchTreeNode *node);

GArray *getCurrentCycle(SearchTreeNode *node);

#endif
