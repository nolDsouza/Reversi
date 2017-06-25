/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2016 Assignment #1 
 * Full Name        : Neil D'Souza
 * Student Number   : s3600251
 * Course Code      : COOSC1076
 * Program Code     : BP096
 * Start up code provided by Paul Miller 
 **********************************************************************/

#include "utility.h"
#include <stdio.h>
#include <string.h> 
#include "shared.h"

/**
 * function required to be used when clearing the buffer. It simply reads
 * each char from the buffer until the buffer is empty again. Please refer
 * to the materials on string and buffer handling in the course for more 
 * information.
 **/
void read_rest_of_line(void)
{
    int ch;
    while(ch = getc(stdin), ch != EOF && ch != NEWLINE);
    clearerr(stdin);
}

/* Can use this in a loop */
void get_menu()
{    
    printf("\n%s\n%s\n%s\n%s\n%s\n%s",
    "Welcome to Reversi!",
    "===================",
    "1. Play a game,",
    "2. Display High Scores",
    "3. Quit the program",
    "Please enter your choice: ");
}







