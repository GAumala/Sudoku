#include "ClockPuzzle.h"

int main( int argc, char *argv[]){
    uint8_t array[] = {3, 4, 5, 6, 6, 7};
    SearchTreeNode *stn = newSearchTreeNode(NULL, array + 2);
    uint8_t *stnContent = (uint8_t *)stn->content;
    printf("stn has: %d. has value %d\n", stnContent, *stnContent);
    printf("Start pos: %d. has value: %d\n", array, *array);
    printf("2nd pos: %d. has value: %d\n", array + 1, *(array + 1));
    printf("4th pos: %d. has value: %d\n", array + 3, *(array + 3));
    return 0;
}
