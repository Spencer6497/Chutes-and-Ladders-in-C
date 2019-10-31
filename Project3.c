/*
 * This program implements a variation of the game Chutes and Ladders. In this game, two players will repeatedly roll
 * a six-sided die to move their piece forward. If they land on a chute, they move backwards, and if they land on a
 * ladder, they move forwards. When a chute, ladder, or haven is landed on, it is removed. Occasionally, a player will land on a space
 * that will direct them to the nearest haven, either backwards or forwards. Logic to handle collisions is included as
 * well.
 */

/* Function Prototypes
 *
 *void output(char[], char *, char *, FILE *);
 *char * findHaven(char *, char[]);
 *char * chuteLadder(char *, char[]);
 *char * move(char *, char *, int, char[], int);
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
    // output new line
    putc('\n', fp1);
}

// Define function to find the nearest haven, given the direction either forwards or backwards
char * findHaven(char *player, char board[]) {
    char *haven; // Create pointer variable to locate the nearest haven
    // if the player must search backwards for a haven
    if (*player == 'B') {
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
    } else if (*player == 'F') {
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
char * chuteLadder(char *player, char board[]) {
    // Calculate distance forwards or backwards
    int distance = (int) (*player - 'n');
    // Change chute or ladder to -
    *player = '-';
    player = player + distance;
    return player;
}

// Define move function to move players, return pointer
char * move(char *p1, char *p2, int playerNum, char board[], int size) {
    int roll = rand() % 6 + 1; // Determine roll of dice via rand function
    p1 = p1 + roll; // Move player according to dice roll
    // Print one line of output followed by a newline
    printf("Player %d rolled %d and moved to square %d", playerNum, roll, p1 - board);
    // Check that the player pointer is within bounds
    if (p1 < board + size) {
        // If player lands on a space, a -, a *, or an H naturally, do not move player
        if (*p1 == ' ' || *p1 == 'H' || *p1 == '-' || *p1 == '*') {
            // Test for collisions
            if ((p1 - board) > 0 && p1 == p2) {
                p1 = p1 - 1;
                printf(" -- Collision! %d is moving back 1 square to %d\n", playerNum, p1 - board);
            }
            printf("\n");
            return p1;
            // If the player lands on a chute
        } else if (*p1 >= 'a' && *p1 <= 'm') {
            p1 = chuteLadder(p1, board);
            printf(" which is a chute and is moving back to square %d\n", p1 - board);
            // Test for collisions
            if ((p1 - board) > 0 && p1 == p2) {
                p1 = p1 - 1;
                printf(" -- Collision! %d is moving back 1 square to %d\n", playerNum, p1 - board);
            }
            return p1;
            // if the player lands on a ladder
        } else if (*p1 >= 'o' && *p1 <= 'z') {
            p1 = chuteLadder(p1, board);
            printf(" which is a ladder and is moving forward to square %d\n", p1 - board);
            // Test for collisions
            if ((p1 - board) > 0 && p1 == p2) {
                p1 = p1 - 1;
                printf(" -- Collision! %d is moving back 1 square to %d\n", playerNum, p1 - board);
            }
            return p1;
            // If a player lands on a forwards haven
        } else if (*p1 == 'F') {
            p1 = findHaven(p1, board);
            printf(" which is a 'F' so is moving forward and lands at %d\n", p1 - board);
            // Test for collisions
            if ((p1 - board) > 0 && p1 == p2) {
                p1 = p1 - 1;
                printf(" -- Collision! %d is moving back 1 square to %d\n", playerNum, p1 - board);
            }
            return p1;
            // If the player lands on a backwards haven
        } else if (*p1 == 'B') {
            p1 = findHaven(p1, board);
            printf(" which is a 'B' so is moving back and lands at %d\n", p1 - board);
            // Test for collisions
            if ((p1 - board) > 0 && p1 == p2) {
                p1 = p1 - 1;
                printf(" -- Collision! %d is moving back 1 square to %d\n", playerNum, p1 - board);
            }
            return p1;
        }
    }
    // Print a newline and return the player pointer as a base case
    printf("\n");
    return p1;
}

// Main function, responsible for initializing players, board, and looping until a player wins, also outputs result
void main() {
    // Initialize board array
    char board[100]="  mHk  H l B He Flq p H  hByHlho H B  jr HFB ir j H  F ku gd  H pjB mH x  BF i H  m oB HlHFBhoH BB ";

    // Seed random number generator
    srand(time(NULL));

    // Initialize both player pointers to the beginning of the array
    char *p1, *p2;
    p1 = board;
    p2 = board;

    // Initialize file pointer for the output textfile
    FILE *fp1;
    fp1 = fopen("output.txt", "w");

    /* Test move and output functions
    for (int i = 0; i < 10; i++) {
        printf("Turn %d: ", i + 1);
        p1 = move(p1, p2, 1, board, SIZE);
        //output(board, p1, p2, fp1);
        p2 = move(p2, p1, 2, board, SIZE);
        output(board, p1, p2, fp1);
    } */

    // Begin main game loop
    while (p1 < board + SIZE && p2 < board + SIZE) {
        p1 = move(p1, p2, 1, board, SIZE);
        p2 = move(p2, p1, 2, board, SIZE);
        output(board, p1, p2, fp1);
    }

    // Determine winner
    if (p1 > p2) {
        printf("Player 1 wins the game!");
    } else {
        printf("Player 2 wins the game!");
    }

    // Close file pointer
    fclose(fp1);
}
