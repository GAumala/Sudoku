#include "ClockPuzzle.h"

uint8_t getClockItemIndex(uint8_t clock[], uint8_t *clockItem){
    return clockItem - clock;
}

json_object *newJSONArray(uint8_t clock[], GArray *state){
    int size = state->len;
    json_object *newArray = json_object_new_array();
    for(int i = 0; i < size; i++){
        SearchTreeNode *node = &g_array_index(state, SearchTreeNode, i);
        uint8_t *item = (uint8_t *) node->content;
        json_object_array_add(newArray, json_object_new_int(
            getClockItemIndex(clock, item)));
    }
    return newArray;
}

void generarHijos(uint8_t clock[], uint8_t clockSize, SearchTreeNode *node){
    uint8_t *nodeClockItem = (uint8_t *) node->content;
    uint8_t clockItemIndex = getClockItemIndex(clock, nodeClockItem);
    uint8_t clockItemValue = *nodeClockItem;
    uint8_t leftIndex = getValidIndex(clockSize, clockItemIndex - clockItemValue);
    uint8_t rightIndex = getValidIndex(clockSize, clockItemIndex + clockItemValue);

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


GArray *findClockSolution(uint8_t clock[], uint8_t clockSize,
    json_object *stateList, uint8_t startPosition){
    SearchTreeNode *root = newSearchTreeNode(NULL, clock + startPosition);
    generarHijos(clock, clockSize, root);
    SearchTreeNode *next = getNextNode(root);
    while(next != NULL){
        GArray *path = getCurrentPath(next);
        if(stateList != NULL && path != NULL){
            json_object_array_add(stateList, newJSONArray(clock, path));
        }
        if(path == NULL){//contradiction, discard
            next->isDeadEnd = 1;
            next = getNextNode(next->parent);
        } else if(path->len == clockSize){//found solution
            next->isDeadEnd = 1;
            next = getNextNode(next->parent);
            return path;
        } else {//no solution yet, go deeper
            if(next->leftChild == NULL)
                generarHijos(clock, clockSize, next);
            next = getNextNode(next);
        }
        }

    return NULL;
}

GArray *findFirstClockSolution(uint8_t clock[], uint8_t clockSize,
    json_object *stateList){
    for(int i = 0; i < clockSize; i++){
        GArray *solution = findClockSolution(clock, clockSize, stateList, i);
        if(solution == NULL){
            json_object_put(stateList);
            stateList = json_object_new_array();
        } else return solution;
    }
    return NULL;
}

GArray *findAllClockSolutions(uint8_t clock[], uint8_t clockSize, json_object *stateList){
    GArray *solutions = g_array_new(FALSE, FALSE, sizeof (GArray));
    for(int i = 0; i < clockSize; i++){
        SearchTreeNode *root = newSearchTreeNode(NULL, clock + i);
        generarHijos(clock, clockSize, root);
        SearchTreeNode *next = getNextNode(root);
        while(next != NULL){
            GArray *path = getCurrentPath(next);
            if(stateList != NULL && path != NULL){
                //printPath(path, clock);
                json_object_array_add(stateList, newJSONArray(clock, path));
            }
            if(path == NULL){//contradiction, discard
                next->isDeadEnd = 1;
                next = getNextNode(next->parent);
            } else if(path->len == clockSize){//found solution
                g_array_append_val(solutions, *path);
                next->isDeadEnd = 1;
                next = getNextNode(next->parent);
            } else {//no solution yet, go deeper
                if(next->leftChild == NULL)
                    generarHijos(clock, clockSize, next);
                next = getNextNode(next);
            }
        }
    }

    return solutions;
}
