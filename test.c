#include "ClockPuzzle.h"
#include <assert.h>

void testGetNextNode() {
    uint8_t array[] = {2, 1, 2};
    uint8_t clockSize = 3;
    printf("new test with: ");
    printClock(array, clockSize);
    printf("create new stn at position 1 of clock\n");
    SearchTreeNode *stn = newSearchTreeNode(NULL, array + 1);
    uint8_t *stnContent = (uint8_t *)stn->content;
    printf("assert that value is 1\n");
    assert(*stnContent == 1);
    printf("generate children of node at position 1 of clock\n");
    generarHijos(array, clockSize, stn);
    uint8_t *leftChildContent = (uint8_t *)stn->leftChild->content;
    uint8_t *rightChildContent = (uint8_t *)stn->rightChild->content;
    printf("assert left child has value 2\n");
    assert((*leftChildContent) == 2);
    printf("assert right child has value 2\n");
    assert((*rightChildContent) == 2);
    SearchTreeNode *nextNode = getNextNode(stn);
    printf("assert that next node is equal to left child\n");
    assert(nextNode == stn->leftChild);
    printf("mark left child as dead end\n");
    nextNode->isDeadEnd = 1;
    printf("assert that next node is equal to right child\n");
    nextNode = getNextNode(stn);
    assert(nextNode == stn->rightChild);
    printf("mark right child as dead end\n");
    nextNode->isDeadEnd = 1;
    nextNode = getNextNode(stn);
    printf("assert that next node is NULL\n");
    assert(nextNode == NULL);

}

int main( int argc, char *argv[]){
    testGetNextNode();
    printf("\n====================\n");
    printf("testing successful!\n");
    printf("====================\n");
    return 0;
}
