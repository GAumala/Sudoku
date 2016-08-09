#include "ClockPuzzle.h"

GArray *findAllClockSolutions(uint8_t clock[], int clockSize){
    return NULL;
}

uint8_t getClockItemIndex(uint8_t clock[], uint8_t *clockItem){
    return clockItem - clock;
}

void generarHijos(uint8_t clock[], uint8_t clockSize, SearchTreeNode *node){
    uint8_t *nodeClockItem = (uint8_t *) node->content;
    uint8_t clockItemIndex = getClockItemIndex(clock, nodeClockItem);
    uint8_t clockItemValue = *nodeClockItem;

    uint8_t leftIndex = abs((clockItemIndex - clockItemValue) % clockSize);
    uint8_t rightIndex = abs((clockItemIndex + clockItemValue) % clockSize);

    SearchTreeNode *leftChild = newSearchTreeNode(node, clock + leftIndex);
    SearchTreeNode *rightChild = newSearchTreeNode(node, clock + rightIndex);

    if(leftIndex == rightIndex)
        leftChild->isDeadEnd = 1;

    node->leftChild = leftChild;
    node->rightChild = rightChild;

}

void printClock(uint8_t clock[], uint8_t clockSize){
    printf("clock: [ %d", clock[0]);
    for(uint8_t i = 1; i < clockSize; i++)
        printf(", %d", clock[i]);
    printf(" ] size: %d\n", clockSize);
}
