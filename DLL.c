#include "DLL.h"


struct Node * createNode(struct Record *record)
{
	struct Node * node = (struct Node *)malloc(sizeof(struct Node));
	node->data = *record;
	node->pNext = NULL;
	node->pPrev = NULL;

	return node;
}


int insertFront(struct Node ** ppHead, struct Node * newNode)
{	if (newNode == NULL)
		return 0;

	if (*ppHead == NULL) //case 1: empty linked list
	{
		*ppHead = newNode;
	}
	else //case 2: non-empty linked list
	{
		newNode->pNext = *ppHead;
		(*ppHead)->pPrev = newNode;
		*ppHead = newNode;
	}
	return 1;
}

void displayRecord(struct Record record)
{
	printf("Movie Title: %s\n",record.title);
	printf("Director: %s\n", record.director);
	printf("Description: %s\n", record.description);
	printf("Genre: %s\n", record.genre);
	printf("Running Time: %d:%d\n", record.runTime.hours, record.runTime.minutes);
	printf("Year: %d\n", record.year);
	printf("Number of times played: %d\n", record.timesPlayed);
	printf("Rating: %d\n\n", record.rating);
}

