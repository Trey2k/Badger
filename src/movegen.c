#include "movegen.h"

void generateWPMoves(sPosition const *pos, sMoveList *list){
    U64 pawnMoves=(pos->bitboards[wP]<<7)&pos->allPieces[black]&pos->ocupied&~fileHMask;//capture left
    U64 possibleMove = pawnMoves&~(pawnMoves-(U64)1);
    while(possibleMove != 0){
        int index = trailingZero(possibleMove);
        if(possibleMove&rank8Mask){
            list->moves[list->count++].move=toMove(index-7, index, 0, wQ, 0);
            list->moves[list->count++].move=toMove(index-7, index, 0, wN, 0);
            list->moves[list->count++].move=toMove(index-7, index, 0, wB, 0);
            list->moves[list->count++].move=toMove(index-7, index, 0, wR, 0);
        }else{
            list->moves[list->count++].move=toMove(index-7, index, 0, 0, moveFlagCAP);
        }

        pawnMoves&=~possibleMove;
        possibleMove=pawnMoves&~(pawnMoves-(U64)1);
    }

    pawnMoves=(pos->bitboards[wP]<<9)&pos->allPieces[black]&pos->ocupied&~fileAMask;//capture right
    possibleMove = pawnMoves&~(pawnMoves-(U64)1);
    while(possibleMove != 0){
        int index = trailingZero(possibleMove);
        if(possibleMove&rank8Mask){
            list->moves[list->count++].move=toMove(index-9, index, 0, wQ, 0);
            list->moves[list->count++].move=toMove(index-9, index, 0, wN, 0);
            list->moves[list->count++].move=toMove(index-9, index, 0, wB, 0);
            list->moves[list->count++].move=toMove(index-9, index, 0, wR, 0);
        }else{
            list->moves[list->count++].move=toMove(index-9, index, 0, 0, moveFlagCAP);
        }
        
        pawnMoves&=~possibleMove;
        possibleMove=pawnMoves&~(pawnMoves-(U64)1);
    }

    pawnMoves=(pos->bitboards[wP]<<8)&pos->empty;//one forward
    possibleMove = pawnMoves&~(pawnMoves-(U64)1);
    while(possibleMove != 0){
        int index = trailingZero(possibleMove);
        if(possibleMove&rank8Mask){
            list->moves[list->count++].move=toMove(index-8, index, 0, wQ, 0);
            list->moves[list->count++].move=toMove(index-8, index, 0, wN, 0);
            list->moves[list->count++].move=toMove(index-8, index, 0, wB, 0);
            list->moves[list->count++].move=toMove(index-8, index, 0, wR, 0);
        }else{
            list->moves[list->count++].move=toMove(index-8, index, 0, 0, 0);
        }
        
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

    if(pos->enPas){
        pawnMoves=(pos->bitboards[wP]<<7)&pos->enPas;//EnPas Left
        possibleMove = pawnMoves&~(pawnMoves-(U64)1);
        while(possibleMove != 0){
            int index = trailingZero(possibleMove);
            list->moves[list->count++].move=toMove(index-7, index, 0, 0, moveFlagEP);
            
            pawnMoves&=~possibleMove;
            possibleMove=pawnMoves&~(pawnMoves-(U64)1);
        }

        pawnMoves=(pos->bitboards[wP]<<9)&pos->enPas;//EnPas Right
        possibleMove = pawnMoves&~(pawnMoves-(U64)1);
        while(possibleMove != 0){
            int index = trailingZero(possibleMove);
            list->moves[list->count++].move=toMove(index-9, index, 0, 0, moveFlagEP);
            
            pawnMoves&=~possibleMove;
            possibleMove=pawnMoves&~(pawnMoves-(U64)1);
        }
    }

}

void generateBPMoves(sPosition const *pos, sMoveList *list){
    U64 pawnMoves=(pos->bitboards[bP]>>7)&pos->allPieces[white]&pos->ocupied&~fileAMask;//capture left
    U64 possibleMove = pawnMoves&~(pawnMoves-(U64)1);
    while(possibleMove != 0){
        int index = trailingZero(possibleMove);
        if(possibleMove&rank1Mask){
            list->moves[list->count++].move=toMove(index+7, index, 0, bQ, 0);
            list->moves[list->count++].move=toMove(index+7, index, 0, bN, 0);
            list->moves[list->count++].move=toMove(index+7, index, 0, bB, 0);
            list->moves[list->count++].move=toMove(index+7, index, 0, bR, 0);
        }else{
            list->moves[list->count++].move=toMove(index+7, index, 0, 0, moveFlagCAP);
        }

        pawnMoves&=~possibleMove;
        possibleMove=pawnMoves&~(pawnMoves-(U64)1);
    }

    pawnMoves=(pos->bitboards[bP]>>9)&pos->allPieces[white]&pos->ocupied&~fileHMask;//capture right
    possibleMove = pawnMoves&~(pawnMoves-(U64)1);
    while(possibleMove != 0){
        int index = trailingZero(possibleMove);
        if(possibleMove&rank1Mask){
            list->moves[list->count++].move=toMove(index+9, index, 0, bQ, 0);
            list->moves[list->count++].move=toMove(index+9, index, 0, bN, 0);
            list->moves[list->count++].move=toMove(index+9, index, 0, bB, 0);
            list->moves[list->count++].move=toMove(index+9, index, 0, bR, 0);
        }else{
            list->moves[list->count++].move=toMove(index+9, index, 0, 0, moveFlagCAP);
        }
        
        pawnMoves&=~possibleMove;
        possibleMove=pawnMoves&~(pawnMoves-(U64)1);
    }

    pawnMoves=(pos->bitboards[bP]>>8)&pos->empty;//one forward
    possibleMove = pawnMoves&~(pawnMoves-(U64)1);
    while(possibleMove != 0){
        int index = trailingZero(possibleMove);
        if(possibleMove&rank1Mask){
            list->moves[list->count++].move=toMove(index+8, index, 0, bQ, 0);
            list->moves[list->count++].move=toMove(index+8, index, 0, bN, 0);
            list->moves[list->count++].move=toMove(index+8, index, 0, bB, 0);
            list->moves[list->count++].move=toMove(index+8, index, 0, bR, 0);
        }else{
            list->moves[list->count++].move=toMove(index+8, index, 0, 0, 0);
        }
        
        pawnMoves&=~possibleMove;
        possibleMove=pawnMoves&~(pawnMoves-(U64)1);
    }

    pawnMoves=(pos->bitboards[bP]>>16)&pos->empty&(pos->empty>>8)&rank5Mask;//Two forward
    possibleMove = pawnMoves&~(pawnMoves-(U64)1);
    while(possibleMove != 0){
        int index = trailingZero(possibleMove);
        list->moves[list->count++].move=toMove(index+16, index, 0, 0, moveFlagPS);
        
        pawnMoves&=~possibleMove;
        possibleMove=pawnMoves&~(pawnMoves-(U64)1);
    }

    if(pos->enPas){
        pawnMoves=(pos->bitboards[bP]>>7)&pos->enPas;//EnPas Left
        possibleMove = pawnMoves&~(pawnMoves-(U64)1);
        while(possibleMove != 0){
            int index = trailingZero(possibleMove);
            list->moves[list->count++].move=toMove(index+7, index, 0, 0, moveFlagEP);
            
            pawnMoves&=~possibleMove;
            possibleMove=pawnMoves&~(pawnMoves-(U64)1);
        }

        pawnMoves=(pos->bitboards[bP]>>9)&pos->enPas;//EnPas Right
        possibleMove = pawnMoves&~(pawnMoves-(U64)1);
        while(possibleMove != 0){
            int index = trailingZero(possibleMove);
            list->moves[list->count++].move=toMove(index+9, index, 0, 0, moveFlagEP);
            
            pawnMoves&=~possibleMove;
            possibleMove=pawnMoves&~(pawnMoves-(U64)1);
        }
    }

}