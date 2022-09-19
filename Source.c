#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <time.h>
#include "Tsur_Log.h"
#pragma warning(disable:4996)


typedef struct ItemNum {

	int num;
	struct ItemNum* next;
	struct ItemNum* prev;
};

struct ItemNum* hEAD = NULL;
struct ItemNum* tAIL = NULL;


struct ItemNum* add(int num);
void printlist();
void replace(struct ItemNum* ptr);
int BubleSort();
void FreeMalloc();
void AddRandomItems(int count);


int main() {
	Log_Init("BubbleLogFile");
	time_t ti;
	srand(time(&ti));

	/*int num;
	printf("Enter numbers: ");
	for (int i = 0; i < 10; i++)
	{
		scanf(" %d", &num);
		add(num);
	}*/

	//printlist();
	//BubleSort();
	
	AddRandomItems(10000);
	FreeMalloc();
	AddRandomItems(100000);
	FreeMalloc();
	return 0;
}


struct ItemNum* add(int num) {
	struct ItemNum* current = (struct ItemNum*)malloc(sizeof(struct ItemNum));
	current->next = NULL;
	current->prev = tAIL;
	current -> num = num;


	if (hEAD == NULL) {

		hEAD = current;
		tAIL = current;
		Log_Event("Created new list");
	}
	else
	{
		tAIL->next = current;
		tAIL = current;
	}
	Log_Event("New Item Added");
}

void printlist() {
	struct ItemNum* printPtr = hEAD;

	while (printPtr != NULL) {

		printf(" %d", printPtr->num);
		printPtr = printPtr->next;
	}

	Log_Event("Printed List");
}

void replace(struct ItemNum* ptr) {

	if (ptr->next == NULL) {
		//error
	}
	else if (ptr == hEAD && ptr->next == tAIL)
	{
		ptr->next = NULL;
		ptr->prev = tAIL;
		tAIL->prev = NULL;
		tAIL->next = ptr;
		tAIL = ptr;
		hEAD = ptr->prev;
	}
	else if (ptr->next == tAIL) {

		ptr->prev->next = ptr->next;
		ptr->next->prev = ptr->prev;
		ptr->next->next = ptr;
		ptr->prev = ptr->next;
		ptr->next = NULL;

		tAIL = ptr;
	}
	else if(ptr==hEAD) {

		ptr->prev = ptr->next;
		ptr->next = ptr->next->next;
		ptr->prev->next = ptr;
		ptr->prev->prev = NULL;
		ptr->next->prev = ptr;

		hEAD = ptr->prev;
		
	}
	else
	{
		
		ptr->prev->next = ptr->next;
		ptr->next->prev = ptr->prev;
		ptr->next->next->prev = ptr;
		ptr->prev = ptr->next;
		ptr->next = ptr->next->next;
		ptr->prev->next = ptr;

	}

}

int BubleSort() {
	unsigned long s1, s2;
	s1 = time(NULL);
	struct ItemNum* ptr = hEAD;
	int signal=1;
	while (signal !=0)
	{
		signal = 0;
		ptr = hEAD;

		while (ptr!=NULL)
		{
			if (ptr->next == NULL) {

			}
			else if (ptr->num > ptr->next->num) 
			{
				replace(ptr);
				signal++;
			}
			ptr = ptr->next;
		}
	}
	s2 = time(NULL);
	printf("\n");
	
	char stringTimeDiff[10000];
	int sortingTime = s2 - s1;
	sprintf(stringTimeDiff, "Sorting took %d seconds", sortingTime);
	Log_Event("Bubble sorted");
	Log_Event(stringTimeDiff);
	return sortingTime;
}

void FreeMalloc() {

	struct ItemNum* remover = hEAD;

	while (hEAD != NULL) {

	    remover=hEAD;
		hEAD = hEAD->next;
		free(remover);
		
	}
	hEAD = NULL;
	Log_Event("Freed all items from list");
}


void AddRandomItems(int count) {
	Log_Event("AddRandomItems function called");
	for (int i = 0; i < count; i++)
	{
		add(rand());
	}
	BubleSort();
}