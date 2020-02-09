#include "program.h"
#include "DLL.h"


struct DLL playList;


void displayOptions()
{
	printf("\n\n-----------OPTIONS--------------\n");
	printf("1. load\n");
	printf("2. store\n");
	printf("3. display\n");
	printf("4. insert\n");
	printf("5. delete\n");
	printf("6. edit\n");
	printf("7. sort\n");
	printf("8. rate\n");
	printf("9. play\n");
	printf("10. shuffle\n");
	printf("11. exit\n\n");
}

void promptOption(char* input)
{
	printf("Action: ");
	fgets(input, 20, stdin);
	arrayToString(input);
}

void arrayToString(char * array)
{
	char * p = strchr(array, '\n');
	if (p != NULL)
		*p = '\0';
}

void load()
{
	FILE *fp;
	char line[1024];
	struct Record * record;
	struct Node * node;

	//read records from moviePlayList.csv line by line	
	fp = fopen("moviePlayList.csv", "r");
	while(fgets(line, 1024, fp) != NULL)
	{
		line[strlen(line) - 1] = '\0';
		record = createRecord(line);
		//check for duplicate (already exists in playlist)
		if (findTitle(record->title) != NULL)
			continue;
		node = createNode(record);
		free(record);//delete record because no longer in use
		insertFront(&playList.pHead, node);
	}

	fclose(fp);
	printf("!!!!Done loading!!!!\n");
};

struct Record * createRecord(char *line)
{
	char * token;
	char * tokenList[8];
	int i = 0;
	struct Record * newRecord = (struct Record *)malloc(sizeof(struct Record));

	//split the line by commas and get tokenList
	token = strtok(line, ",");
	while(token)
	{
		tokenList[i++] = token;
		token = strtok(NULL, ",");
	}
	
	//get record members	
	strcpy(newRecord->title, tokenList[0]);
	strcpy(newRecord->director, tokenList[1]);
	strcpy(newRecord->description, tokenList[2]);
	strcpy(newRecord->genre, tokenList[3]);
	newRecord->runTime.hours = atoi(strtok(tokenList[4], ":"));
	newRecord->runTime.minutes = atoi(strtok(NULL, ":"));
	newRecord->year = atoi(tokenList[5]);
	newRecord->timesPlayed = atoi(tokenList[6]);
	newRecord->rating = atoi(tokenList[7]);

	return newRecord;
}

void display()
{
	char option;	
	
	printf("What do you want to display?\n");
	printf("  Type 1 to display all movies\n");
	printf("  Type 2 to display all moves of a director\n");
	printf("  Type 3 to display all movies of a year\n");
	
	option = fgetc(stdin);
	fgetc(stdin);
	
	if (option == '1')
		displayAllRecords();
	else if (option == '2')
		displayRecordsOfDirector();
	else if (option == '3')
		displayRecordsOfYear();
	else
		printf("Invalid option!\n");
}

void displayAllRecords()
{
	struct Node * curNode = playList.pHead;
	
	printf("--------All Movies--------\n");
	
	while(curNode != NULL)
	{	
		displayRecord(curNode->data);
		printf("\n");

		curNode = curNode->pNext;		
	}

	printf("---------End displaying all movies--------\n");
}

void displayRecordsOfDirector()
{
	struct Node * curNode = playList.pHead;
	char director[50];

	//ask for a director
	printf("Name of the director? ");
	fgets(director, 50, stdin);
	arrayToString(director);
		
	printf("--------All Movies of %s--------\n", director);
	
	while(curNode != NULL)
	{	
		if (strcmp(curNode->data.director, director) == 0)
		{
			displayRecord(curNode->data);
			printf("\n");
		}
		curNode = curNode->pNext;		
	}

	printf("---------End displaying all movies of %s--------\n", director);
}

void displayRecordsOfYear()
{
	struct Node * curNode = playList.pHead;
	char year[5];

	//ask for a year
	printf("What year? ");
	fgets(year, 5, stdin);
	arrayToString(year);
	fgetc(stdin);
		
	printf("--------All Movies of %d--------\n", atoi(year));
	
	while(curNode != NULL)
	{	
		if (curNode->data.year == atoi(year))
		{
			displayRecord(curNode->data);
			printf("\n");
		}
		curNode = curNode->pNext;		
	}

	printf("---------End displaying all movies of %s--------\n", year);
}

void edit()
{
	char director[50];
	char title[100];
	int nMovies = 0;
	struct Record * record;

	//ask for a director
	printf("What director whose records do you want to edit? ");
	fgets(director, 50, stdin);
	arrayToString(director);

	nMovies = countRecordsOfDirtr(director);
	
	if (nMovies == 0)
		printf("Director %s does not have any movies in this playlist\n", director);
	else if (nMovies == 1)
	{
		record = findDirector(director);
		editRecord(record);
	}
	else
	{
		printf("Director %s has %d movies in this playlist\n", director, nMovies);
		printf("Choose a movie title of director %s to edit: ", director);
		fgets(title, 100, stdin);
		arrayToString(title);
		
		record = findTitle(title);
		editRecord(record);
	}
}

int countRecordsOfDirtr(char *director)
{
	struct Node * curNode = playList.pHead;
	int nMovies = 0;

	while(curNode != NULL)
	{	
		if (strcmp(curNode->data.director, director) == 0)
			nMovies++;
		curNode = curNode->pNext;		
	}
	return nMovies;
}

struct Record * findDirector(char *director)
{
	struct Node * curNode = playList.pHead;

	while(curNode != NULL)
	{	
		if (strcmp(curNode->data.director, director) == 0)
			return &(curNode->data);
		curNode = curNode->pNext;		
	}
	return NULL;
}

struct Record * findTitle(char *title)
{
	struct Node * curNode = playList.pHead;

	while(curNode != NULL)
	{	
		if (strcmp(curNode->data.title, title) == 0)
			return &(curNode->data);
		curNode = curNode->pNext;		
	}
	return NULL;
}

void editRecord(struct Record *record)
{
	char field[24];	

	//display the current record
	printf("\n---Current record---\n");
	displayRecord(*record);
	
	//ask for a field to edit
	printf("\nWhat field do you want to edit (title, director, description, genre, running time, year, number of times played, rating)?  ");
	fgets(field, 24, stdin);
	arrayToString(field);
	
	if (strcmp(field, "title") == 0)
		editTitle(record);
	else if (strcmp(field, "director") == 0)
		editDirector(record);
	else if (strcmp(field, "description") == 0)
		editDescription(record);
	else if (strcmp(field, "genre") == 0)
		editGenre(record);
	else if (strcmp(field, "running time") == 0)
		editRunTime(record);
	else if (strcmp(field, "year") == 0)
		editYear(record);
	else if (strcmp(field, "number of times played") == 0)
		editTimesPlayed(record);
	else if (strcmp(field, "rating") == 0)
		editRating(record);
	else
		printf("Invalid field!\n");
}

void editTitle(struct Record * record)
{
	char title[100];
	printf("new title: ");
	fgets(title, 100, stdin);
	arrayToString(title);
	strcpy(record->title, title);
}

void editDirector(struct Record * record)
{
	char director[50];
	printf("new director: ");
	fgets(director, 50, stdin);
	arrayToString(director);
	strcpy(record->director, director);
}

void editDescription(struct Record * record)
{
	char description[200];
	printf("new description: ");
	fgets(description, 200, stdin);
	arrayToString(description);
	strcpy(record->description, description);
}

void editGenre(struct Record * record)
{
	char genre[200];
	printf("new genre: ");
	fgets(genre, 20, stdin);
	arrayToString(genre);
	strcpy(record->genre, genre);
}

void editRunTime(struct Record * record)
{
	char time[6];
	char *token;
	printf("new running time: ");
	fgets(time, 6, stdin);
	arrayToString(time);
	
	token = strtok(time, ":");
	record->runTime.hours = atoi(token);
	token = strtok(NULL, ":");
	record->runTime.minutes = atoi(token);
}

void editYear(struct Record * record)
{
	char year[5];
	printf("new year: ");
	fgets(year, 5, stdin);
	arrayToString(year);
	record->year = atoi(year);
}

void editTimesPlayed(struct Record * record)
{
	char timesPlayed[5];
	printf("new number of times played: ");
	fgets(timesPlayed, 5, stdin);
	arrayToString(timesPlayed);
	record->timesPlayed = atoi(timesPlayed);
}

void editRating(struct Record * record)
{
	char rating[2];
	printf("new rating: ");
	fgets(rating, 2, stdin);
	arrayToString(rating);
	record->rating = atoi(rating);
}

void rate()
{
	char title[100];
	struct Record *record;

	printf("What movie do you want to rate? ");
	fgets(title, 100, stdin);
	arrayToString(title);

	record = findTitle(title);

	editRating(record);
}

void play(int secs)
{
	char title[100];
	struct Record *record;
	struct Node * curNode;
	struct Node * startNode;

	//users choose a movie to start playing
	printf("Pick a movie title to start playing: ");
	fgets(title, 100, stdin);
	arrayToString(title);

	//find the start node (node of the chosen movie)
	curNode = playList.pHead;
	while(curNode != NULL)
	{	
		if (strcmp(curNode->data.title, title) == 0)
			break;
		curNode = curNode->pNext;		
	}
	if (curNode == NULL)
	{	
		printf("The movie %s is not found!\n", title);
		return;
	}

	startNode = curNode;
	//play from this movie to the end of the playlist
	while (curNode != NULL)
	{
		displayRecord(curNode->data);
		sleep(secs);
		curNode = curNode->pNext;
	}
	
	curNode = playList.pHead;
	//play from the beginning of the playlist to before the chosen movie
	while (curNode != startNode)
	{
		displayRecord(curNode->data);
		sleep(secs);
		curNode = curNode->pNext;
	}
}

void store()
{
	FILE *fp;
	char line[1024] = "";
	struct Node * node = playList.pHead;
	char stringRep[5];

	//write all records to moviePlayList.csv
	fp = fopen("moviePlayList.csv", "w");
	
	while (node != NULL)
	{
		printf("--%s\n", node->data.title);
		strcat(line, node->data.title);
		strcat(line, ",");
		strcat(line, node->data.director);
		strcat(line, ",");
		strcat(line, node->data.description);
		strcat(line, ",");
		strcat(line, node->data.genre);
		strcat(line, ",");
		sprintf(stringRep, "%d", node->data.runTime.hours);
		strcat(line, stringRep);
		strcat(line, ":");
		sprintf(stringRep, "%d", node->data.runTime.minutes);
		strcat(line, stringRep);
		strcat(line, ",");
		sprintf(stringRep, "%d", node->data.year);
		strcat(line, stringRep);
		strcat(line, ",");
		sprintf(stringRep, "%d", node->data.timesPlayed);
		strcat(line, stringRep);
		strcat(line, ",");
		sprintf(stringRep, "%d", node->data.rating);
		strcat(line, stringRep);
		strcat(line, "\n");
		
		fprintf(fp, "%s", line);
		strcpy(line, "");
		node = node->pNext;
	}

	fclose(fp);
	printf("!!!!Done storing!!!!\n");
}

