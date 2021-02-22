#ifndef BOARD_H
#define BOARD_H
#include "defs.h"
#include "bitboards.h"

/************************
    External Functions
*************************/
extern int fileRankToSquare(int file, int rank);
extern boolean parseFen(sPosition *pos, char *fen);
extern U64 allBoards(sPosition *pos);

/************************
    Internal Functions
*************************/

static void resetBoard(sPosition *pos);

#endif