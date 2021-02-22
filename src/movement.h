#ifndef MOVEMENT_H
#define MOVEMENT_H
#include "defs.h"
#include "board.h"

typedef struct {
	int move;
	int score;
} sMove;


typedef struct {
	sMove moves[maxPositionMoves];
	int count;
} sMoveList;

extern int getFrom(int move);
extern int getTo(int move);
extern int getCapture(int move);
extern int getPromoted(int move);
extern int toMove(int from, int to, int capture, int promotion, int flag);
#endif