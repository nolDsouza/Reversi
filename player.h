/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2016 Assignment #1 
 * Full Name        : Neil D'Souza
 * Student Number   : s3600251
 * Course Code      : COOSC1076
 * Program Code     : BP096
 * Start up code provided by Paul Miller 
 **********************************************************************/
#include "shared.h"
#include "gameboard.h"
#include "utility.h"

#ifndef PLAYER_H
#define PLAYER_H
/* the maximum length of a player name */
#define NAMELEN 20
/* the number of characters allowed when the user is entering the coordinates
 * for a game
 */

#define TUPLELEN 3
/* The number of chars in a valid co-ordinate */
 
#define DELIMS ","
/* what are the attributes of a player? They have a score, a token (either BLUE
 * or RED), and a score
 */
struct player
{
    char name[NAMELEN + 1];
    enum cell token;
    unsigned score;
};

/* Function's to set all player attributes */
BOOLEAN init_first_player(struct player* human, enum cell * token);
/* Token passed will be first player's, second player will get the opposite */
BOOLEAN init_second_player(struct player * computer, enum cell token);

/* Get user input and provide early validation to set up 
 * x and y co-ordinates. These are passed to apply_move */
BOOLEAN make_move(struct player * player, game_board board);

/* Function to get a random int to be assigned to an enum cell */
int get_color(void);

#endif /* ifndef PLAYER_H */
