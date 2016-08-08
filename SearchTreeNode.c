#include "SearchTreeNode.h"

SearchTreeNode *newSearchTreeNode(SearchTreeNode *parent, void *content){
    SearchTreeNode *stn = (SearchTreeNode *) malloc(sizeof(SearchTreeNode));
    stn->leftChild = NULL;
    stn->rightChild = NULL;
    stn->parent = parent;
    stn->content = content;
    stn->isDeadEnd = 0;
    return stn;
}

void generarHijos(uint8_t clock[], uint8_t clockSize, SearchTreeNode *node){

}

SearchTreeNode *getNextNode(SearchTreeNode *node){
    return NULL;
}

GArray *getCurrentCycle(SearchTreeNode *node){
    return NULL;
}
