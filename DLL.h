#ifndef DLL_H
#define DLL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct Duration
{
	int hours;
	int minutes;
};

struct Record
{
	char title[100];
	char director[50];
	char description[200];
	char genre[20];
	struct Duration runTime;
	int year;
	int timesPlayed;
	int rating;
};

struct Node
{
	struct Record data;
	struct Node * pNext;
	struct Node * pPrev;
};

struct DLL
{
	struct Node * pHead;
};


//create a node from a record
struct Node * createNode(struct Record *record);


//insert a node to a the front of a DLL given its pHead
//return 1 is successful, return 0 otherwise
int insertFront(struct Node ** ppHead, struct Node * newNode);


//display all info of a record
void displayRecord(struct Record record);

#endif
