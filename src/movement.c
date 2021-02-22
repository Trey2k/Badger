#include "movement.h"

/*
0000 0000 0000 0000 0000 0100 0000
0000 0000 0000 0000 0000 0111 1111 -> From 0x7F
0000 0000 0000 0011 1111 1000 0000 -> To >> 7, 0x7F
0000 0000 0011 1100 0000 0000 0000 -> Captured >> 14, 0xF | 0x7C000
0000 0000 0100 0000 0000 0000 0000 -> EP 0x40000
0000 0000 1000 0000 0000 0000 0000 -> Pawn Start 0x80000
0000 1111 0000 0000 0000 0000 0000 -> Promoted Piece >> 20, 0xF | 0xF00000
0001 0000 0000 0000 0000 0000 0000 -> Castle 0x1000000
*/

// GetFrom value from move int
int getFrom(int move) {
	return move & 0x7F;
}

//Get the to square from a movement int
int getTo(int move) {
	return (move >> 7) & 0x7F;
}

//Get the piece captured from a movement int
int getCapture(int move) {
	return (move >> 14) & 0xF;
}

//Get the piece promote to from a move int
int getPromoted(int move) {
	return (move >> 20) & 0xf;
}

//Convert movement info into a move int
int toMove(int from, int to, int capture, int promotion, int flag) {
	return (from | (to << 7) | (capture << 14) | (promotion << 20) | flag);
}
