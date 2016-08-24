#include <stdio.h>
#include <stdlib.h>

int evaluateSolution(int *per, int *clock, int length){
	for (int i = 0; i < length - 1; i++){
		if ((per[(i + 1) % length] != ((per[i] + clock[per[i]]) % length))
			&& (per[(i + 1) % length] != (max(length + per[i] - clock[per[i]], per[i] - clock[per[i]]) % length))){
			return 0;
		}
	}
	return 1;
}

void printClock(int* clock, int length){
	for (int i = 0; i < length; i++){
		printf("%d,", clock[i]);
	}
	printf("\n");
}

void swap(int *x, int *y){
	int temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

int* clockCpy(int *clock, int length){
	int *new_array;
	new_array = (int*)malloc(sizeof(int)*length);

	for (int i = 0; i < length; i++){
		new_array[i] = i;
	}
	
	return new_array;
}

void permute(int *tmp, int l, int r, int *clock, int length){
	int i;
	if (l == r){
		if (evaluateSolution(tmp, clock, length)){
			printClock(tmp, length);
			//tmp es la solucion
		}
	} else {
		for (i = l; i <= r; i++) {
			swap((tmp + l), (tmp + i));
			permute(tmp, l + 1, r, clock, length);
			swap((tmp + l), (tmp + i));
		}
	}
}

//int main()
//{
//	//int clock[] = { 6, 5, 1, 4, 2, 1, 6, 4, 2, 1, 5, 2 };
//	/*
//	Soluciones
//	3,7,11,9,8,10,5,4,2,1,6,0
//	3,7,11,9,10,5,4,2,1,8,6,0
//	7,3,11,9,8,10,5,4,2,1,6,0
//	7,3,11,9,10,5,4,2,1,8,6,0
//	9,8,10,5,4,2,3,7,11,1,6,0
//	9,10,5,4,2,3,7,11,1,8,6,0
//	*/
//	int clock[] = { 1, 1, 1 };
//	int length = (sizeof(clock) / sizeof(clock[0]));
//	int *tmp = clockCpy(clock, length);
//	permute(tmp, 0, length - 1, clock, length);
//	return 0;
//}
