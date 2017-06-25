/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2016 Assignment #1 
 * Full Name        : Neil D'Souza
 * Student Number   : s3600251
 * Course Code      : COOSC1076
 * Program Code     : BP096
 * Start up code provided by Paul Miller 
 **********************************************************************/
#include <time.h>
#include "shared.h"
#include "player.h"
#include "gameboard.h"


#ifndef GAME_H
#define GAME_H
/* Array boundires */
#define UPPERBOUND 7
#define LOWERBOUND 0
#define UPPERBOUND 7
#define UNDERBOUND LOWERBOUND 
#define OVERBOUND 9 

/* Direction changes */
#define RAISE -1
#define LOWER 1
#define INCREASE LOWER
#define DECREASE RAISE

/* Attributes of a move a player wants to make, to be passed a parameters */
struct move
{
    unsigned x,y;
    int width,height;
    enum cell color;
};

/* Initialises all structures, then loops the fucntions required to play game 
 * and return a winner */
struct player * play_game(struct player * human, struct player * computer);

/* This function will check for adjacencies in each direction
 * if successfull it will set up a move struct in that direction 
  *to see if any pieces can be captured */
BOOLEAN apply_move(game_board board, unsigned y, unsigned x,
                   enum cell player_token);

/* Counts how many tokens of a given color are on the given board */
unsigned game_score(game_board board, enum cell player_token);

/* Swaps the pointers that point to the player structs in main */
void swap_players(struct player ** first, struct player ** second);

/* Uses a given move to see if pieces can be captured, 
 * if so the boolean passed tells the function to capture them */
BOOLEAN capture_pieces(game_board board, const struct move *move, 
	BOOLEAN passed);
#endif /* ifndef GAME_H */
