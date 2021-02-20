#ifndef BOARD_H
#define BOARD_H
#include "constants.h"
#include "bitboards.h"

extern const int fileRankToSquare[8][8];

extern int parseFen(sPosition *pos, char *fen);

#endif