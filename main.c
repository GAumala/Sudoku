#include "ClockPuzzle.h"
#include <string.h>

void printExample(){
    printf("EXAMPLE: \n");
    printf("If you have clock that looks like this: [3, 1, 3, 1 ,2, 3]\n");
    printf("pass it using the -i flag like this:\n");
    printf("$ ./main -i 3 1 3 1 2 3\n");
    printf("The output will be a JSON formatted list of states.\n");
    printf("This particular clock yields this result:\n\n");
    printf("[ [ 1, 0 ], [ 1, 0, 3 ], [ 1, 0, 3, 2 ], [ 1, 0, 3, 2, 5 ], [ 1, 0, 3, 2 ], ");
    printf("[ 1, 0, 3 ], [ 1, 0, 3, 4 ], [ 1, 0, 3, 4, 2 ], [ 1, 0, 3, 4, 2, 5 ] ]\n\n");
    printf("Each number is a position in the clock array.\nThe last item is a valid solution.\n");

}
void printHelp(){
    printf("Hands of fate puzzle solver using a Depth First Algorithm.\n Flags:\n");
    printf("-i\tset the numbers to use as face values of the clock\n");
    printf("-h\tprint this help message\n");
    printExample();
}

int getInputStartIndex(int argc, char *argv[]){
    char *startFlag = "-i";
    for(int i = 0; i < argc; i++){
        if(strcmp(startFlag, argv[i]) == 0)
            return i + 1;
    }

    return -1;
}

uint8_t *parseClockFromArguments(int argc, char *argv[], int startIndex, uint8_t clockSize){
    uint8_t *clock = (uint8_t *) malloc(sizeof(uint8_t) * clockSize);
    for(int i = startIndex; i < argc; i++){
        clock[i - startIndex] = atoi(argv[i]);
    }
    return clock;
}

void displayArgumentError(){
    printf("ERROR: No -i flag found\n");
    printExample();
    exit(1);
}

int main( int argc, char *argv[]){
    if(argc == 2 && strcmp(argv[0], "-h") == 0)
        printHelp();
    else if(argc < 2)
        printHelp();
    else {
        int startIndex = getInputStartIndex(argc, argv);
        if(startIndex == -1){
            displayArgumentError();
        }
        uint8_t clockSize = argc - startIndex;
        uint8_t *clock = parseClockFromArguments(argc, argv, startIndex, clockSize);

        json_object *json = json_object_new_array();
        GArray *solution = findFirstClockSolution(clock, clockSize, json);
        if(solution == NULL){
            printf("[]\n");
        } else {
            printf("%s\n", json_object_to_json_string(json));
        }
    }
}
