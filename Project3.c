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
 * 10/10/19
 * Project3
 */

#include <stdio.h>

void main() {
    // Initialize board array
    char board[100]="  mHk nH l B He Flq p H  hByHlho H B  jr HFB ir j H  F ku gd  H pjB mH x  BF i H  m oB HlHFBhoH BB ";
    // Initialize both player pointers to the beginning of the array
    char *p1, *p2 = board;
}