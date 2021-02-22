#ifndef IO_H
#define IO_H
#include "movement.h"

extern char *squareToString(const int sq);
extern char *moveToString(const int move);
extern char pieceToChar(const int piece);

extern void printBoard(sPosition *pos);
#endif