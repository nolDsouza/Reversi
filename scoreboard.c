/***********************************************************************
* COSC1076 - Advanced Programming Techniques
* Semester 2 2016 Assignment #1 
* Full Name        : Neil D'Souza
* Student Number   : s3600251
* Course Code      : COOSC1076
* Program Code     : BP096
* Start up code provided by Paul Miller 
**********************************************************************/

#include "scoreboard.h"

/**
* initalise the scoreboard so that the scores for each element of the array
* is set to 0.
**/

void init_scoreboard(score scores[MAX_SCORES])
{
	int i;    
    
	for (i=0; i<MAX_SCORES; i++)
	{
	scores[i].score = 0;
	}
}


/**
* insert the top scorer from the last game played in sorted order according
* to their score 
**/
BOOLEAN add_to_scoreboard(score scores[MAX_SCORES], struct player * winner)
{
	int i,j;

	for (i = 0; i < MAX_SCORES; i++)
	{
		if ((*winner).score > scores[i].score)
		{
			for (j = MAX_SCORES-1; j > i; j--)
			{   
		        /* decrease j value so the index is in array boundries */ 
				scores[j] = scores[j-1];
				/* Shift all scores right, 
				 * if full the lowest score is overwritten */ 
			}
			/* Add winner score in correct place */
			scores[i] = *winner;
			return TRUE;
			/* No need to continue iteration */
		}
	} 
	/* Exiting the loop means all scores are greater that given winner */
	printf("You did not score high enough to be added to the scoreboard.\n");
	return FALSE;
}

/**
* display the scores in the scoreboard according to their order. Your output
* should match that provided in the assignment specification.
**/
void display_scores(score scores[MAX_SCORES])
{
	int k = 0;
	printf("Reversi - Top Scores\n====================\n");
	printf("----------------------------\n");
	printf("Name                 | Score\n");
	printf("----------------------------\n");
	/* Print all scores before the first NULL name index */
	while (scores[k].score != 0 && k < MAX_SCORES)
	{
		printf("%-20s | %d\n", scores[k].name, scores[k].score);
		k++;
	}
	printf("----------------------------\n");
}
