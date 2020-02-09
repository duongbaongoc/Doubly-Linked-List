#include "program.h"


int main()
{
	char option[20];

	do
	{
		displayOptions();
		promptOption(option);
		
		if (strcmp(option, "load") == 0)	
			load();
		else if (strcmp(option, "store") == 0)
			store();
		else if (strcmp(option, "display") == 0)
			display();	
		else if (strcmp(option, "edit") == 0)
			edit();
		else if (strcmp(option, "rate") == 0)
			rate();
		else if (strcmp(option, "play") == 0)
			play(2);
	
	} while (strcmp(option, "exit") != 0);
	
	store();

	return 0;
}
