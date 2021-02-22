#ifndef BITBOARDS_H
#define BITBOARDS_H

#include "defs.h"
#include "board.h"

/************************
    External Functions
*************************/

extern void initBitboards(sPosition *pos);
extern void removeFromBitboard(U64 *bitboard, int sq);
extern void addToBitboard(U64 *bitboard, int sq);
extern int countBits(U64 bitboard);
extern int trailingZero(U64 bitboard);
extern int getPieceAtSquare(sPosition *pos, int sq);

extern void printBitBoard(U64 bitboard);

#endif