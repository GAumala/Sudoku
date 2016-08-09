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


SearchTreeNode *getNextNode(SearchTreeNode *node){
    return NULL;
}

GArray *getCurrentCycle(SearchTreeNode *node){
    return NULL;
}
