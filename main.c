#include "ClockPuzzle.h"

int main( int argc, char *argv[]){
    uint8_t array[] = {3, 4, 5, 1, 2, 1};
    SearchTreeNode *stn = newSearchTreeNode(NULL, array + 2);
    uint8_t *stnContent = (uint8_t *)stn->content;
    printf("stn has: %d. has value %d\n", stnContent, *stnContent);
    generarHijos(array, 6, stn);
    uint8_t *leftChildContent = (uint8_t *)stn->leftChild->content;
    uint8_t *rightChildContent = (uint8_t *)stn->rightChild->content;
    printf("stn leftchild has value %d\n", *leftChildContent);
    printf("stn rightchild has value %d\n", *rightChildContent);
    printf("Start pos: %d. has value: %d\n", array, *array);
    printf("2nd pos: %d. has value: %d\n", array + 1, *(array + 1));
    printf("4th pos: %d. has value: %d\n", array + 3, *(array + 3));
    return 0;
}
