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
#include "player.h"
#ifndef SCOREBOARD_H
#define SCOREBOARD_H
#define MAX_SCORES 10
/* Score is a player, so can get name as well */ 
typedef struct player score;

/* Set scores to 0 */
void init_scoreboard(score scores[MAX_SCORES]);
/* Add winner details to scoreboard */
BOOLEAN add_to_scoreboard(score scores[MAX_SCORES], struct player * winner);

/* Print out top 10 winners and their scores */
void display_scores(score scores[MAX_SCORES]);
#endif /* ifndef SCOREBOARD_H */
