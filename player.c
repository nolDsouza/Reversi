/***********************************************************************
* COSC1076 - Advanced Programming Techniques
* Semester 2 2016 Assignment #1 
* Full Name        : Neil D'Souza
* Student Number   : s3600251
* Course Code      : COOSC1076
* Program Code     : BP096
* Start up code provided by Paul Miller 
**********************************************************************/
#include "player.h"
#include "game.h"

/**
* These two functions initialise the player structure at the beginning of the 
* game. In both cases, you should initialise the whole structure to known safe
* values and then prompt the user for their name. In the init_first_player() 
* function you should then select a color at random for this player using the 
* rand() function. This token should be assigned to the first player's token and
* also returned via the token pointer. In init_second_player() you should just
* test the value of token and assign the opposite color to the second player.
**/




BOOLEAN init_first_player(struct player* first, enum cell * token)
{
    char name[NAMELEN+EXTRACHARS];

    printf("\n%s", "Please enter the first player's name: ");

    if ( fgets (name, NAMELEN+EXTRACHARS, stdin)==NULL )
    {
        return FALSE;
    }
    if (strcspn(name, "\n") == 0)
    {
        return FALSE;
    }

    if(name[strlen(name)-1]!=NEWLINE)
    {
        printf("Error: buffer overflow.%s",
        " Please try again, entering less data.\n");
        read_rest_of_line();
        /* Recursing on buffer overflow 
         * until the user inputs a valid name or quits */
        if (init_first_player(first, token))
            return TRUE;
        return FALSE;
    }
    /* Actual initialisation, that is assignments of player attributes */  
    strcpy((*first).name, name);
    (*first).token = get_color();
    (*first).score = 0;
    return TRUE;

}


BOOLEAN init_second_player(struct player * second, enum cell token)
{
    char name[NAMELEN+EXTRACHARS];

    printf("%s", "Please enter the second first player's name: ");

    if ( fgets (name, NAMELEN+EXTRACHARS, stdin)==NULL )
    {
        return FALSE;
    }
    if ( strcspn(name, "\n") == 0)
    {
        return FALSE;
    }
    if(name[strlen(name)-1]!=NEWLINE)
    {
        printf("Error: buffer overflow.%s",
        " Please try again, entering less data.\n");
        read_rest_of_line();
        if (init_second_player(second, token))
            return TRUE;
        return FALSE;
    }
    /* Same as the first, except the token passed is flipped */  
    strcpy((*second).name, name);
    (*second).score = 0; 
    if (token == RED)
    {
        (*second).token = BLUE;
    }
    else
    {
        (*second).token = RED;
    }	
    return TRUE;
}

/**
* prompts the user for a comma-separate pair of coordinates for a move in the
* game. Each move, if valid, must capture at least one enemy piece by 
* surrounding a sequence of one or more enemy pieces with two pieces of our 
* own: one being the new piece to be placed and the other a piece already 
* on the board. This function then validates that a valid move has been entered
* calls the apply_move function to do the actual work of capturing pieces.
**/
BOOLEAN make_move(struct player * human, game_board board)
{
    char *ptr;
    unsigned digit[TUPLELEN-1];
    /* Subtract 1 for comma */
    BOOLEAN required = TRUE;
    char coord[TUPLELEN+EXTRACHARS];
    int count = 0;

    /* Will loop through the input move process until
    user inputs digits with a "," delim */
    do 
    {

        count = 0;
        /* Input handling */
        printf("Please enter x and y coordinates"); 
        printf(" seperated by a comma for the piece you wish to place: \n");

        if ( fgets (coord, TUPLELEN+EXTRACHARS, stdin)==NULL )
        {
            return FALSE;
        }
        if ( strcspn(coord, "\n") == 0)
        {
            return FALSE;
        }
        if(coord[strlen(coord)-1]!=NEWLINE)
        {
            /* First error message is if a string 
             * with more than 3 chars is inputted */
            printf("Error: buffer overflow.%s",
            " Please try again, entering less data.\n");
            read_rest_of_line();
            continue;
        }

        /* Get first token, hopefully a coordinate*/
        ptr = strtok(coord, ",");

        while(ptr!=NULL)
        {

            char * end;
            digit[count] = (int) strtol(ptr, &end, 0);

            if(*end)
            {
                /* Second error is for incorrect String 
                 * inputs/format from buffer */
                printf("Error: invalid coordniates\n");
                ptr = NULL;
            }
            else
            {
                /* get second token, use NULL to access previous string */
                ptr = strtok(NULL, "\n");
                count++;
                /* Count will be incremented if strtol conversion is made */
            }
        }

        /* count == 2 means two digits were returned from strtol */
        if (count != 2)
        {  
            /* Third error is for non numeric data, subset of second error */
            printf("Error: you did not enter valid coordinates.%s", 
                " Please try again.\n");
        }
        else if (!apply_move(board, digit[1], digit[0], (*human).token))
        {  
            /* apply_move will make the actual move if possible */ 
            printf("Error: the move you attempted was not valid.\n");
        }
        else
        {
            /* if apply_move returned true, then a 
            *valid capture has been executed and we can exit the loop */
            required = FALSE;
        }

    } while (required);

    return TRUE;
}

int get_color(void)
{
    time_t t;

    /* Intialize random number generator */
    srand((unsigned) time(&t));

    /* return an int between 1 and 2(no. of colors) */
    return(rand() %NUM_COLORS + 1);

}