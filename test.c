#include "ClockPuzzle.h"
#include <assert.h>

int main( int argc, char *argv[]){
    uint8_t array[] = {3, 4, 5, 1, 2, 1};
    uint8_t clockSize = 6;
    printf("new test with: ");
    printClock(array, clockSize);
    printf("create new stn at position 2 of clock\n");
    SearchTreeNode *stn = newSearchTreeNode(NULL, array + 2);
    uint8_t *stnContent = (uint8_t *)stn->content;
    printf("assert that value is 5\n");
    assert(*stnContent == 5);
    printf("generate children of node at position 2 of clock\n");
    generarHijos(array, clockSize, stn);
    uint8_t *leftChildContent = (uint8_t *)stn->leftChild->content;
    uint8_t *rightChildContent = (uint8_t *)stn->rightChild->content;
    printf("assert left child has value 1\n");
    assert((*leftChildContent) == 1);
    printf("assert right child has value 4\n");
    assert((*rightChildContent) == 4);

    printf("testing successful!\n");
    return 0;
}
