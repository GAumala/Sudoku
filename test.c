#include "ClockPuzzle.h"
#include <assert.h>

void testGetNextNode() {
    uint8_t array[] = {2, 1, 2};
    uint8_t clockSize = 3;
    printf("\n====================\n");
    printf("get next node\n");
    printf("====================\n");
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
void testGetCurrentCycle() {
    uint8_t array[] = {3, 1, 3, 1, 2, 3};
    uint8_t clockSize = 6;
    printf("\n====================\n");
    printf("get current cycle\n");
    printf("====================\n");
    printf("new test with: ");
    printClock(array, clockSize);
    SearchTreeNode *stn1 = newSearchTreeNode(NULL, array + 1);
    SearchTreeNode *stn0 = newSearchTreeNode(stn1, array);
    SearchTreeNode *stn3 = newSearchTreeNode(stn0, array + 3);
    SearchTreeNode *stn4 = newSearchTreeNode(stn3, array + 4);
    SearchTreeNode *stn2 = newSearchTreeNode(stn4, array + 2);
    SearchTreeNode *stn5 = newSearchTreeNode(stn2, array + 5);
    GArray * path = getCurrentPath(stn5);
    printf("assert that path has the length of the clock\n");
    assert(path->len == clockSize);
    SearchTreeNode *pathnode = &g_array_index(path, SearchTreeNode, 0);
    printf("assert that the first element of the path is stn1\n");
    assert(stn1->content == pathnode->content);
    pathnode = &g_array_index(path, SearchTreeNode, clockSize - 1);
    printf("assert that the last element of the path is stn5\n");
    assert(stn5->content == pathnode->content);

    printPath(path, array);

    printf("add stn1 as child of stn5 (create contradiction)\n");
    SearchTreeNode *stnLast = newSearchTreeNode(stn5, array + 1);
    printf("assert that contradicted path is null\n");
    path = getCurrentPath(stnLast);
    assert(path == NULL);
    printf("assert that incomplete path is not null\n");
    path = getCurrentPath(stn4);
    assert(path != NULL && path->len < clockSize);
}

void testFindAllSolutions(){
    uint8_t array[] = {3, 1, 3, 1, 2, 3};
    uint8_t clockSize = 6;
    printf("\n====================\n");
    printf("find all solutions\n");
    printf("====================\n");
    printf("new test with: ");
    printClock(array, clockSize);
    GArray *solutions = findAllClockSolutions(array, clockSize, 0);
    printf("assert that solution is unique\n");
    assert(solutions->len == 1);
    printf("assert that solution goes through positions: 1, 0, 3, 4, 2, 5\n");
    GArray *solutionPath = &g_array_index(solutions, GArray, 0);
    SearchTreeNode *solutionNode = &g_array_index(solutionPath, SearchTreeNode, 0);
    assert(solutionNode->content == array + 1);
    solutionNode = &g_array_index(solutionPath, SearchTreeNode, 1);
    assert(solutionNode->content == array);
    solutionNode = &g_array_index(solutionPath, SearchTreeNode, 2);
    assert(solutionNode->content == array + 3);
    solutionNode = &g_array_index(solutionPath, SearchTreeNode, 3);
    assert(solutionNode->content == array + 4);
    solutionNode = &g_array_index(solutionPath, SearchTreeNode, 4);
    assert(solutionNode->content == array + 2);
    solutionNode = &g_array_index(solutionPath, SearchTreeNode, 5);
    assert(solutionNode->content == array + 5);
}

void testGenerarHijos(){
    uint8_t array[] = {3, 1, 3, 1, 2, 3};
    uint8_t clockSize = 6;
    printf("\n====================\n");
    printf("generar hijos\n");
    printf("====================\n");
    printf("new test with: ");
    printClock(array, clockSize);
    SearchTreeNode *stn = newSearchTreeNode(NULL, array + 2);
    generarHijos(array, clockSize, stn);
    printf("assert leftChild of 3@2 is 3@5\n");
    assert(stn->leftChild->content == array + 5);
    printf("assert rightChild of 3@2 is 3@5\n");
    assert(stn->rightChild->content == array + 5);
    printf("assert leftChild of 3@2 is dead  end\n");
    assert(stn->leftChild->isDeadEnd);


    stn = newSearchTreeNode(NULL, array + 5);
    generarHijos(array, clockSize, stn);
    printf("assert leftChild of 3@5 is 3@2\n");
    assert(stn->leftChild->content == array + 2);
    printf("assert rightChild of 3@2 is 3@5\n");
    assert(stn->rightChild->content == array + 2);
}
int main( int argc, char *argv[]){
    testGetNextNode();
    testGetCurrentCycle();
    testGenerarHijos();
    testFindAllSolutions();
    printf("\n====================\n");
    printf("testing successful!\n");
    printf("====================\n");
    return 0;
}
