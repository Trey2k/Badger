#include "movement.h"
#include "io.h"

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

boolean makeMove(sPosition *pos, int move){
    int to = getTo(move);
    int from = getFrom(move);
    int piece = getPieceAtSquare(pos, from);
    int captured = getCapture(move);
    int promotion = getPromoted(move);

    if(piece == empty){
        return FALSE;
    }

    if(to >= 64 || to < 0 || from >= 64 || from < 0){
        return FALSE;
    }

    ASSERT(pos->hisPly >= 0 && pos->hisPly < maxGameMoves);

    pos->history[pos->hisPly].move = move;
    pos->history[pos->hisPly].enPas = pos->enPas;
    pos->history[pos->hisPly].castlePerms = pos->castlePerms;
    pos->history[pos->hisPly].fiftyMove = pos->fiftyMove;

    if(piece == wP || piece == bP || move&moveFlagCAP || move&moveFlagEP){
        pos->fiftyMove = 0;
    }else{
        pos->fiftyMove++;
    }

    if(move&moveFlagEP){
        if (pos->side==white){
            removeFromBitboard(&pos->bitboards[bP], to+8);
        }else{
            removeFromBitboard(&pos->bitboards[wP], to-8);
        }
    }else if(captured != empty){
        removeFromBitboard(&pos->bitboards[captured], to);
    }
    removeFromBitboard(&pos->bitboards[piece], from);

    if(promotion != empty){
        piece = promotion;
    }

    addToBitboard(&pos->bitboards[piece], to);

    pos->hisPly++;
    pos->side ^= 1;
    updatePosition(pos);
    return TRUE;
}

void undoMove(sPosition *pos){
    pos->hisPly--;

    int move = pos->history[pos->hisPly].move;
   
    pos->enPas = pos->history[pos->hisPly].enPas;
    pos->castlePerms = pos->history[pos->hisPly].castlePerms;
    pos->fiftyMove = pos->history[pos->hisPly].fiftyMove;
    pos->side ^= 1;

    int to = getTo(move);
    int from = getFrom(move);
    int piece = getPieceAtSquare(pos, to);
    int captured = getCapture(move);
    int promotion = getPromoted(move);

    ASSERT(piece != empty);
    ASSERT(to < 64 && to >= 0 && from < 64 && from >= 0);
    ASSERT(pos->hisPly >= 0 && pos->hisPly < maxGameMoves);

    removeFromBitboard(&pos->bitboards[piece], to);

    if(move&moveFlagEP){
        if (pos->side==white){
            addToBitboard(&pos->bitboards[bP], to+8);
        }else{
            addToBitboard(&pos->bitboards[wP], to-8);
        }
    }else if(captured != empty){
        addToBitboard(&pos->bitboards[captured], to);
    }

    if(promotion != empty){
        if(pos->side==white){
            piece = wP;
        }else{
            piece = bP;
        }
    }

    addToBitboard(&pos->bitboards[piece], from);
    updatePosition(pos);
}