/*
 * This program implements a variation of the game Chutes and Ladders. In this game, two players will repeatedly roll
 * a six-sided die to move their piece forward. If they land on a chute, they move backwards, and if they land on a
 * ladder, they move forwards. When a space is landed on, it is removed. Occasionally, a player will land on a space
 * that will direct them to the nearest haven, either backwards or forwards. Logic to handle collisions is included as
 * well.
 *
 * Spencer Peace
 * CSC 362-001
 * Dr. Richard Fox
 * 10/17/19
 * Project3
 */

/* Function Prototypes
 *
 *void output(char[], char *, char *, FILE *);
 *char * findHaven(char, char *, char[]);
 *char * chuteLadder();
 *char * move(char *, char *, char[] *, int, int);
 *
*/

// Include IO functions for file output
#include <stdio.h>

// Include functions for random number generation & seeding RNG
#include <stdlib.h>
#include <time.h>

// Define constant for size of the board
const int SIZE = 100;

// Define function to output the current game board to disk file on a single line
void output(char board[], char *p1, char *p2, FILE *fp1) {
    char *a = board; // Character pointer used to iterate through board
    // Iterate through the board
    while(*a != '\0') {
        // If current position is player 1, print 1
        if (a == p1) {
            putc('1', fp1);
        // If current position is player 2, print 2
        } else if (a == p2) {
            putc('2', fp1);
        // Otherwise, print whatever is at the current position
        } else {
            putc(*a, fp1);
        }
        // Move the current position along
        a++;
    }
}

// Define function to find the nearest haven, given the direction either forwards or backwards
char * findHaven(char direction, char *player, char board[]) {
    char *haven; // Create pointer variable to locate the nearest haven
    // if the player must search backwards for a haven
    if (direction == 'B') {
        // Iterate down from the player's position to the board[0]
        for (haven = player; haven >= board; haven--) {
            // If there are no more havens backwards, return the starting position
            if (haven == board) {
                return board;
            // Otherwise (if haven found), return this haven
            } else if (*haven == 'H') {
                // Reset haven to *
                *haven = '*';
                return haven;
            }
        }
    // if the player must search forwards for a haven
    } else if (direction == 'F') {
        // Iterate up from the players position to board + SIZE
        for (haven = player; haven <= board + SIZE; haven++) {
            // If there are no more havens forwards, do not move the player
            if (haven == board + SIZE) {
                return player;
            // Otherwise, if haven found, return this haven
            } else if (*haven == 'H') {
                // reset haven to *
                *haven = '*';
                return haven;
            }
        }
    }
}

// Define chuteLadder function to move players if they land on a chute or a ladder
char * chuteLadder() {

}

// Define move function to move players, return pointer
char * move(char *p1, char *p2, int playerNum, char *board[], int size) {

}

// Main function, responsible for initializing players, board, and looping until a player wins, also outputs result
void main() {
    // Initialize board array
    char board[100]="  mHk  H l B He Flq p H  hByHlho H B  jr HFB ir j H  F ku gd  H pjB mH x  BF i H  m oB HlHFBhoH BB ";

    // Seed random number generator
    srand(time(NULL));

    // Initialize both player pointers to the beginning of the array
    char *p1 = board, *p2 = board;

    // Initialize file pointer for the output textfile
    FILE *fp1;
    fp1 = fopen("output.txt", "w");

    // Test
    //output(board, p1, p2, fp1);

    // Begin main game loop

}