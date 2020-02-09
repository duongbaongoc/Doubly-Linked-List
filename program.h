#ifndef program_h
#define program_h

#include <stdio.h>
#include <string.h>
#include <unistd.h> //sleep


//display 11 options for user
void displayOptions();

//ask user for an option
void promptOption(char* input);

//load: read all records from moviePlayList.csv into a DLL
void load();

//create a record from a line (in moviePlayList.csv)
struct Record * createRecord(char *line);

//display: display records from DLL to the screen
void display();

//print out all records in the DLL
void displayAllRecords();

//print out all movies of a given director
void displayRecordsOfDirector();

//print out all movies of a given year
void displayRecordsOfYear();

//give a array of chars, replace the first '\n' by '\0'
void arrayToString(char *array);

//allow users to edit a record (users choice) of a director (user choice)
void edit();

//return the number of records that a director has
int countRecordsOfDirtr(char *director);

//return the first record found of a given director
struct Record * findDirector(char *director);

//return the record given its title
struct Record * findTitle(char *title);

//allow users to edit all fields of a given record
void editRecord(struct Record *record);

//allow users to edit the title of a given record
void editTitle(struct Record * record);

//allow users to edit the director of a given record
void editDirector(struct Record * record);

//allow users to edit the description of a given record
void editDescription(struct Record * record);

//allow users to edit the genre of a given record
void editGenre(struct Record * record);

//allow users to edit the running time of a given record
void editRunTime(struct Record * record);

//allow users to edit the year of a given record
void editYear(struct Record * record);

//allow users to edit the number of times played of a given record
void editTimesPlayed(struct Record * record);

//allow users to edit the rating of a given record
void editRating(struct Record * record);

//allow users to rate a movie
void rate();

//allow users to choose a movie, for each movie on the list in order from this chosen movie, display its content for n seconds
void play(int secs);

//save all current records in the DLL to the text file
void store();

#endif
