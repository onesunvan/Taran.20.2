#include "stdlib.h"
#include "stdio.h"
#include "memory.h"

struct Node {
	int data;
	struct Node * next;
};

void printArray(int * array, size_t size) {
	if (size <= 0) {
		return;
	}
	printf("%d", array[0]);
	int i;
	for (i = 1; i < size; i++) {
		printf(", %d", array[i]);
	}
	printf("\n");
}

void printList(struct Node * list) {
	if (list == NULL) {
		printf("List is empty");
	} else {
		struct Node * iterator = list;
		printf("%d", iterator->data);
		while (iterator->next != NULL) {
			iterator = iterator->next;
			printf(", %d", iterator->data);
		}
		printf("\n");
	}
}


void addToList(int element, struct Node ** pListHead) {
	struct Node * listHead = *pListHead;
	if (*pListHead == NULL) {
		*pListHead = malloc(sizeof(struct Node));
		(*pListHead)->data = element;
		(*pListHead)->next = NULL;
	} else {
		struct Node * iterator = listHead;
		while (iterator->next != NULL) {
			iterator = iterator->next;
		}
		iterator->next = malloc(sizeof(struct Node));
		iterator->next->data = element;
		iterator->next->next = NULL;
	}
}

void sortArray(int array[], size_t size, struct Node ** pGrowingList, struct Node ** pDecreasingList) {
	int i;
	int j;
	int position;
	int swap;
	int * temporalArray = malloc(sizeof(int) * size);
	memcpy(temporalArray, array, sizeof(int) * size);
	for ( i = 0 ; i < size - 1; i++ ) {
		position = i;
		for ( j = i + 1; j < size; j++ ) {
			if ( temporalArray[position] > temporalArray[j] ) {
				position = j;
			}
		}
		if ( position != i ) {
			swap = temporalArray[i];
			temporalArray[i] = temporalArray[position];
			temporalArray[position] = swap;
		}
	}
	for (i = 0; i < size; i++) {
		addToList(temporalArray[i], pGrowingList);
		addToList(temporalArray[size - 1 - i], pDecreasingList);
	}
}

#define N 5

int main(void) {
	int array[N];
	printf("Hello\n");
	memset(array, 0, sizeof(int) * N);
	int i;
	for (i = 0; i < N; i++) {
		printf("Enter %d element of array\n", i);
		fflush(stdout);
		scanf("%i", &(array[i]));
		printArray(array, N);
	}

	struct Node * growingList = NULL;
	struct Node * decreasingList = NULL;
	sortArray(array, N, &growingList, &decreasingList);
	printf("Growing list\n");
	printList(growingList);

	printf("Decreasing list\n");
	printList(decreasingList);
	return 0;
}
