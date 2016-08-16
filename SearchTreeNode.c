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

    //both children are dead end. Let's make sure that this node is also a dead end.
    node->isDeadEnd = 1;
    return node->parent;
}
