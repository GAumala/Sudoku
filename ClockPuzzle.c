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

void printPath(GArray *array, uint8_t clock[]){
    int length = array->len;
    printf("Path is:");
    for(int i = 0; i < length; i++){
        SearchTreeNode *node = &g_array_index(array, SearchTreeNode, i);
        uint8_t *content = (uint8_t *)node->content;
        uint8_t index = getClockItemIndex(clock, content);
        printf(" %d@%d ", *content, index);
    }
    printf("\n");
}

GArray *getCurrentPath(SearchTreeNode *node){
    GArray *array = g_array_new(FALSE, FALSE, sizeof (SearchTreeNode));
    SearchTreeNode *next = node->parent;
    while(next != NULL){
        if(next->content == node->content)
            return NULL;//contradiction, this path is useless

        g_array_prepend_val(array, *next);
        next = next->parent;
    }
    g_array_append_val(array, *node);
    return array;
}

void printClock(uint8_t clock[], uint8_t clockSize){
    printf("clock: [ %d", clock[0]);
    for(uint8_t i = 1; i < clockSize; i++)
        printf(", %d", clock[i]);
    printf(" ] size: %d\n", clockSize);
}
