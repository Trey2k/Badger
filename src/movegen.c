#include "movegen.h"

void generateMoves(sPosition const *pos, sMoveList *list){
    U64 pawnMoves=(pos->bitboards[wP]<<7)&pos->allPieces[black]&pos->ocupied&~rank8Mask&~fileHMask;//capture left
    U64 possibleMove = pawnMoves&~(pawnMoves-(U64)1);
    while(possibleMove != 0){
        int index = trailingZero(possibleMove);
        list->moves[list->count++].move=toMove(index-7, index, 0, 0, moveFlagCAP);

        pawnMoves&=~possibleMove;
        possibleMove=pawnMoves&~(pawnMoves-(U64)1);
    }

    pawnMoves=(pos->bitboards[wP]<<9)&pos->allPieces[black]&pos->ocupied&~rank8Mask&~fileAMask;//capture right
    possibleMove = pawnMoves&~(pawnMoves-(U64)1);
    while(possibleMove != 0){
        int index = trailingZero(possibleMove);
        list->moves[list->count++].move=toMove(index-9, index, 0, 0, moveFlagCAP);
        
        pawnMoves&=~possibleMove;
        possibleMove=pawnMoves&~(pawnMoves-(U64)1);
    }

    pawnMoves=(pos->bitboards[wP]<<8)&pos->empty&~rank8Mask;//one forward
    possibleMove = pawnMoves&~(pawnMoves-(U64)1);
    while(possibleMove != 0){
        int index = trailingZero(possibleMove);
        list->moves[list->count++].move=toMove(index-8, index, 0, 0, 0);
        
        pawnMoves&=~possibleMove;
        possibleMove=pawnMoves&~(pawnMoves-(U64)1);
    }

    pawnMoves=(pos->bitboards[wP]<<16)&pos->empty&(pos->empty<<8)&rank4Mask;//Two forward
    possibleMove = pawnMoves&~(pawnMoves-(U64)1);
    while(possibleMove != 0){
        int index = trailingZero(possibleMove);
        list->moves[list->count++].move=toMove(index-16, index, 0, 0, moveFlagPS);
        
        pawnMoves&=~possibleMove;
        possibleMove=pawnMoves&~(pawnMoves-(U64)1);
    }


}