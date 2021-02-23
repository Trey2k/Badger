#ifndef MOVEGEN_H
#define MOVEGEN_H

#include "defs.h"
#include "movement.h"

const U64 rankMasks8[8];
const U64 fileMasks8[8];
const U64 diagonalMasks8[15];
const U64 antiDiagonalMasks8[15];

extern void generateAllMoves(sPosition const *pos, sMoveList *list);

U64 reverse(U64 n);
U64 hAndVMoves(U64 s, sPosition const *pos);
U64 dAndAntiDMoves(U64 s, sPosition const *pos);

void generateWPMoves(sPosition const *pos, sMoveList *list);
void generateBPMoves(sPosition const *pos, sMoveList *list);
void generateNMoves(sPosition const *pos, sMoveList *list);
void generateNMoves(sPosition const *pos, sMoveList *list);
void generateKMoves(sPosition const *pos, sMoveList *list);
void generateBMoves(sPosition const *pos, sMoveList *list);
void generateRMoves(sPosition const *pos, sMoveList *list);
void generateQMoves(sPosition const *pos, sMoveList *list);

#endif

