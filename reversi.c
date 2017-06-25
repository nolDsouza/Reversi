/***********************************************************************
* COSC1076 - Advanced Programming Techniques
* Semester 2 2016 Assignment #1 
* Full Name        : Neil D'Souza
* Student Number   : s3600251
* Course Code      : COOSC1076
* Program Code     : BP096
* Start up code provided by Paul Miller 
**********************************************************************/


#include <stdio.h>
#include <string.h> 
#include "reversi.h"

/**
* the hear of the program. The main() function in particular should 
* manage the main menu for the program.
**/




int main(void)
{	
    score scrboard[MAX_SCORES];
    char line[LINELEN + EXTRACHARS];
    struct player human, computer, *winner = NULL;
    /* initialise the scoreboard */
    init_scoreboard(scrboard);    
    /* in a loop: display the main menu */
    do
    {

        get_menu();

        /* Check that the fgets didn't reutrn EOF */
        if ( fgets (line, LINELEN + EXTRACHARS, stdin)==NULL )
        {
            printf("That is not a valid option. Please try again.\n");
            continue;
        }
        /* line is not NULL, so check that there was no buffer overflow */
        if(line[strlen(line)-1]!=NEWLINE)
        {
            printf("Error: buffer overflow.%s ",  
            "Please try again, entering less data.\n");
            read_rest_of_line();
            continue;
        }

        /* Remove new line character */
        line[strcspn(line, "\n")] = 0;
        /* This should also detect if the user solely pressed enter */

        /* perform the requested task */

        if (!strcmp(line, "1"))
        {
            /* play a game and add the winner to the scoreboard */ 
            winner = play_game(&human, &computer);
            if (winner != NULL)
            {
                printf("The winner is %s with %d tokens!\n", 
                (*winner).name, (*winner).score);
                add_to_scoreboard(scrboard, winner);           
            }
        }
        else if (!strcmp(line, "2"))
        {                            
            /* display scores */
            display_scores(scrboard);

        }      

    } while (strcmp(line, "3"));
    /* Will exit the loop only when user inputs 3 */

    /* quit the program */
    return EXIT_SUCCESS;
}

