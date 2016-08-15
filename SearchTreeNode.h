#ifndef SEARCHTREENODE
#define SEARCHTREENODE

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

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

SearchTreeNode *getNextNode(SearchTreeNode *node);


#endif
