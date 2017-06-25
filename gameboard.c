/***********************************************************************
* COSC1076 - Advanced Programming Techniques
* Semester 2 2016 Assignment #1 
* Full Name        : Neil D'Souza
* Student Number   : s3600251
* Course Code      : COOSC1076
* Program Code     : BP096
* Start up code provided by Paul Miller 
**********************************************************************/
#include "gameboard.h"
#include "player.h"



/**
* initialise the game board to be consistent with the screenshot provided
* in your assignment specification. 
*
* All squares should be initialised to be blank other than the four
* squares in the middle of the board. In that case they are initialised to 
* appropriate colored tokens
**/
void init_game_board(game_board board)
{
    int i,j;

    /* Set all square's to blank */
    for (i=0; i<BOARD_HEIGHT; i++)
    { 
        for (j=0; j<BOARD_WIDTH; j++)
        {
            board[i][j] = BLANK;    
        }
    }
    /* Assign initial four squares */
    board[3][3] = RED;
    board[4][4] = RED;
    board[4][3] = BLUE;
    board[3][4] = BLUE;
}

/**
* display the board as specified in the assignment specification. You should 
* make every effort to create a board consistent with the screenshots in the 
* assignment specification. 
**/
void display_board(game_board board, struct player * first,
struct player * second)
{
    int i,j; 

    /* Remove the returned new lines so names can be printed */
    (*first).name[strcspn((*first).name,"\n")] = 0;
    (*second).name[strcspn((*second).name,"\n")] = 0;

    printf(
    "===========================================%s", 
    "====================================\n");

    printf("Player One's Details\n");
    printf("--------------------\n");
    printf("Name: %s\tScore: %d\tToken Color: ", 
    (*first).name, (*first).score);

    /* Get the correct color token to be printed */
    print_token((*first).token);

    printf(
    "\n------------------------------------------%s",
    "--------------------------------------\n");

    printf("Player Two's Details\n");
    printf("--------------------\n");
    printf("Name: %s\tScore: %d\tToken Color: ", 
        (*second).name, (*second).score);
    print_token((*second).token);

    printf(
    "\n------------------------------------------%s",
    "--------------------------------------\n");

    /* Print the column number */
    printf("%s\n%s",
    "     1   2   3   4   5   6   7   8",	
    "====================================");

    /* Iterate over the gameboard, printing relative to the cell value */
    for (i=0; i<BOARD_HEIGHT; i++)
    {
        /* Print the row number */
        printf("\n %d |", (i+1));
        for (j=0; j<BOARD_WIDTH; j++)
        {
            /* Print correct color if required */
            if (board[i][j] == RED)
            { 
                printf("%s%s%s%s", COLOR_RED, " 0 ", COLOR_RESET, "|");
            }
            else if (board[i][j] == BLUE)
            {
                printf("%s%s%s%s", COLOR_BLUE, " 0 ", COLOR_RESET, "|");
            }
            else
            {
                printf ("%*s", COLUMN_WIDTH, "|");
            }
            /* Default blank column is 4 spaces wide */
        }
        printf("\n------------------------------------");
    }   
    printf("\n====================================\n");	

}

/* Function to print a given player's token to console with correct color */
void print_token(enum cell color)
{
    if (color == 1)
        printf("%s%c%s", COLOR_RED, '0', COLOR_RESET);
    else if (color == 2) 
        printf("%s%c%s", COLOR_BLUE, '0', COLOR_RESET);  
    else
        printf("%s", "Token failed to initialize\n");     
}