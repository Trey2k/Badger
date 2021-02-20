#ifndef BITBOARDS_H
#define BITBOARDS_H

#include "constants.h"
#include "board.h"

extern void initBitboards(sPosition *pos);
extern void addToBitboard(U64 *bitboard, int sq);
extern void printBitBoard(U64 bb);

#endif