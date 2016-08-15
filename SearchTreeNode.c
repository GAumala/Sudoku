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
    if(node->isDeadEnd)
        return node->parent;

    SearchTreeNode *child = node->leftChild;
    if(!child->isDeadEnd)
        return child;
    child = node->rightChild;
    if(!child->isDeadEnd)
        return child;

    return node->parent;
}

GArray *getCurrentCycle(SearchTreeNode *node){
    return NULL;
}
