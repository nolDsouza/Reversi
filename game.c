/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2016 Assignment #1 
 * Full Name        : Neil D'Souza
 * Student Number   : s3600251
 * Course Code      : COOSC1076
 * Program Code     : BP096
 * Start up code provided by Paul Miller 
 **********************************************************************/
#include "game.h"

/**
 * The heart of the game itself. You should do ALL initialisation required 
 * for the game in here or call function required for that purpose. For example
 * both players should be initialised from here, you should seed the random 
 * number generator, that kind of thing. 
 *
 * Next, you should set the initial player - the initial player is the player 
 * whose token was set by initialisation to RED. 
 *
 * Next, you will need to manage the game loop in here. In each loop of the 
 * game, you should display the game board, including player scores 
 * display whose turn it is, etc in the format specified in the assignment
 * specification. Finally at the end of each turn you will calculate the score 
 * for each player you will calculate their score and store it and then you 
 * will need to swap the current player and other player 
 * using the swap_player() function. 
 * 
 * A game will end when either player presses enter or ctrl-d on a newline. 
 * 
 * When you detect a request to end the game, you should do a final calculation
 * of the scores for the two players and return the player with the highest
 * score.
 **/
struct player * play_game(struct player * first, struct player * second)
{	
	game_board board;
	enum cell token;
	struct player **current, **other, *winner;
    BOOLEAN game_on = TRUE;
    int count;
  
  	/* Initialise firs player */
	if(!init_first_player(first, &(*first).token)) 
 		return NULL;
 	/* These functions return FALSE if the user want to go back,
 	 to main menu that is enter or ctrl d */

 	/* Take first token so second player can be given the oppoite */ 
	token = (*first).token;

    if(!init_second_player(second, token))
    	return NULL;

    /* Assign first player to whichever contains RED token */
    if (token == RED)
    {	
   		current = &first;
		other = &second;
    }
    else if (token == BLUE)
	{
    	current = &second;
    	other = &first;
    }

    /* Set cells to initial colours */
	init_game_board(board);
	count = 0;

 	do 
	{	
		/* Using count to maintain first player consistency on board */
		if (count % 2)
            display_board(board, second, first);
        else
	    	display_board(board, first, second);
	
    	printf("It's %s's turn.\n", (**current).name);
    	/* This loop can only end when the player elects to quit */
	    if (!make_move(*current, board))
	    {
	    	game_on = FALSE;
	    }
	    /* Count tokens after successful move*/
	    (*first).score = game_score(board, (*first).token);
	    (*second).score = game_score(board, (*second).token);
	    /* This was ignored first iteration as scores are initialised to 0 */

	    /* Change turns */
	    swap_players(current, other);
		count++; 
	    
 	} while (game_on);

 	/* Use counted scores to determine a winner, 
 	 * will do so even if game didn't start */
 	if ((*first).score == (*second).score)
 	{
 		printf("\nIt's draw!\n");
 		return NULL;
 	}
 	else if((*first).score > (*second).score)
 	{
 		winner = first;
 	}
 	else
 	{
 		winner = second;
 	}
 	return winner;
}
        

/**
 * does the work of applying the move requested by the user to the game board.
 * It iterates over all the directions from the coordinate specified to see
 * whether there are any pieces that can be captured. If there are no pieces
 * that can be captured in any direction, it is an invalid move.
 **/
BOOLEAN apply_move(game_board board, unsigned y, unsigned x,
                   enum cell player_token)
{
	
	unsigned captured_pieces = 0;
	enum cell oppose = BLUE;
	struct move move;

	/* fourth error checking the actual digit's are inside board boundries */
	if (y==UNDERBOUND || x==UNDERBOUND || y==OVERBOUND || x==OVERBOUND)
	{
		return FALSE;
	}
	
	/* Decrement co-ordinates for 0 based array indeces */
	move.y = --y;
	move.x = --x;

	/* Fifth error (in this case) is if the coord is not a blank space */
	if (board[y][x] != BLANK)
	{
		return FALSE;
	}

	/* Setting up the move struct so it can be passed as a parameter */
 	move.color = player_token;
	
	/* Must check the opposing color is adjacent */
	if (player_token == BLUE)
	    --oppose;		

	/* Check the directions adjacencies */ 
	
	if (y != LOWERBOUND && board[y-1][x] == oppose )		
	{	/*NORTH*/ 
	    move.height = RAISE; 
		move.width = 0;
	    captured_pieces += capture_pieces(board, &move, FALSE);
	} 
	if (y != UPPERBOUND && board[y+1][x] == oppose)
	{	/*SOUTH*/
	    move.height = LOWER; 
		move.width = 0;
	    captured_pieces += capture_pieces(board, &move, FALSE);
	} 
	if (x != UPPERBOUND && board[y][x+1] == oppose)
	{	/*EAST*/
	    move.height = 0; 
		move.width = INCREASE;
	    captured_pieces += capture_pieces(board, &move, FALSE);
	} 
	if (x != LOWERBOUND && board[y][x-1] == oppose)
	{	/*WEST*/
	    move.height = 0; 
		move.width = DECREASE;
	    captured_pieces += capture_pieces(board, &move, FALSE);
	} 
	if (y != LOWERBOUND && x != UPPERBOUND && board[y-1][x+1] == oppose)
	{	/*NORTH_EAST*/
		
	    move.height = RAISE; 
		move.width = INCREASE;
	    captured_pieces += capture_pieces(board, &move, FALSE);
	} 
	if (y != LOWERBOUND && x != LOWERBOUND && board[y-1][x-1] == oppose)
	{	/*NORTH_WEST*/
	    move.height = RAISE; 
		move.width = DECREASE;
	    captured_pieces += capture_pieces(board, &move, FALSE);
	} 
	if (y != UPPERBOUND && x != UPPERBOUND && board[y+1][x+1] == oppose)
	{	/*SOUTH_EAST*/
	    move.height = LOWER; 
		move.width = INCREASE;
	    captured_pieces += capture_pieces(board, &move, FALSE);
	} 
	if (y != UPPERBOUND && x != LOWERBOUND && board[y+1][x-1] == oppose)
	{	/*SOUTH_WEST*/
	    move.height = LOWER; 
		move.width = DECREASE;
	    captured_pieces += capture_pieces(board, &move, FALSE);
	} 
	
	/* captured_pieces>1 indicates a capture was made, else there wasn't */
	if (captured_pieces)
		return TRUE;
	return FALSE;
	/* Sixth error occurs if there was no way to capture opposing tokens
	 * from the given move */
}
/**
 * simply count up how many locations contain the player_token 
 * specified on the game_board.
 **/
unsigned game_score(game_board board, enum cell player_token)
{
    int i,j;
    unsigned score = 0;
    for (i=0; i<BOARD_HEIGHT; i++)
    { 
        for (j=0; j<BOARD_WIDTH; j++)
		{
		    if (board[i][j] == player_token)
			score++;
		}
    }
    return score;
}

/**
 * swap the two player pointers passed in so that first points to the player
 * pointer that originally contained the second player and vice versa.
 **/
void swap_players(struct player ** first, struct player ** second)
{
	/* Temporary pointer will store first pointer 
	 * so that it is not lost in swawp */
	struct player *tempp = *first;
	*first = *second;
	*second = tempp; 
}



BOOLEAN capture_pieces(game_board board, const struct move *move, 
	BOOLEAN passed)
{
	/* This function needs the values of most variables from apply_move */
	enum cell oppose = BLUE;
	int y = (*move).y, x = (*move).x;	
	BOOLEAN moved;

	/* Getting opposing token again */
	if ((*move).color == BLUE)
			--oppose;
	do
	{
		/* Final conditions before tokens are flipped */ 
	    if (passed)
	    {
	    	/* This is checked first so it can capture the original 
	    	 * co-ordinates */
			board[y][x] = (*move).color;	
	    }
	    /* Now move up the board, in the direction the struct move was given */
	    y += (*move).height;
	    x += (*move).width;
	    moved = TRUE;

	    if (y>UPPERBOUND || x>UPPERBOUND || y<LOWERBOUND || x<LOWERBOUND)
	    {
	    	/* Once in here, the array is out of bounds and
	    	 * obviously no captures are possible in this direction */
			return FALSE;
	    }

	    if (moved && board[y][x] == (*move).color)
	    {
	    	/* Here we know a valid capture can be made, 
	    	 * so recurse the fucntion, this time letting it know
	    	 * if it can flip all opposite tokens on directional path */
			if (!passed)
	        {
	        	capture_pieces(board, move, TRUE);
	        }
	        return 1;
	        /* boolean is just an int so TRUE can be return of 1 capture */
        }

	} while (board[y][x] == oppose);

	/* Exitting the loop means that there was a blank space on path, 
	 * and no possible captures */
	return FALSE;
}



