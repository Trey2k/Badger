#include "movegen.h"

const U64 rankMasks8[8] ={
        0xFFull, 0xFF00ull, 0xFF0000ull, 0xFF000000ull, 0xFF00000000ull, 0xFF0000000000ull, 
        0xFF000000000000ull, 0xFF00000000000000ull
};

const U64 fileMasks8[8] = {
        0x101010101010101ull, 0x202020202020202ull, 0x404040404040404ull, 0x808080808080808ull,
        0x1010101010101010ull, 0x2020202020202020ull, 0x4040404040404040ull, 0x8080808080808080ull
};

const U64 diagonalMasks8[15] = {
        0x1ull, 0x102ull, 0x10204ull, 0x1020408ull, 0x102040810ull, 0x10204081020ull, 0x1020408102040ull,
        0x102040810204080ull, 0x204081020408000ull, 0x408102040800000ull, 0x810204080000000ull,
        0x1020408000000000ull, 0x2040800000000000ull, 0x4080000000000000ull, 0x8000000000000000ull
};

const U64 antiDiagonalMasks8[15] = {
    0x80ull, 0x8040ull, 0x804020ull, 0x80402010ull, 0x8040201008ull, 0x804020100804ull, 0x80402010080402ull,
    0x8040201008040201ull, 0x4020100804020100ull, 0x2010080402010000ull, 0x1008040201000000ull,
    0x804020100000000ull, 0x402010000000000ull, 0x201000000000000ull, 0x100000000000000ull
};

U64 reverse(U64 n) {
  U64 ans = 0;
  for(int i = 63; i >= 0; i--){
    ans |= (n & 1) << i;
    n>>=1;
  }
  return ans;
}

U64 hAndVMoves(U64 s, sPosition const *pos){
	U64 binaryS=(U64)1<<s;
	U64 possibilitiesHorizontal = (pos->ocupied - (U64)2 * binaryS) ^ reverse(reverse(pos->ocupied) - (U64)2 * reverse(binaryS));
	U64 possibilitiesVertical = ((pos->ocupied&fileMasks8[s%8]) - ((U64)2 * binaryS)) ^ 
            reverse(reverse(pos->ocupied&fileMasks8[s%8]) - ((U64)2 * reverse(binaryS)));
            
	return (possibilitiesHorizontal&rankMasks8[s/8]) | (possibilitiesVertical&fileMasks8[s%8]);
}

U64 dAndAntiDMoves(U64 s, sPosition const *pos){
	U64 binaryS=(U64)1<<s;
	U64 possibilitiesDiagonal = ((pos->ocupied&diagonalMasks8[(s /8) + (s%8)]) - ((U64)2 * binaryS)) ^ reverse(reverse(pos->ocupied&diagonalMasks8[(s/8) + (s%8)]) - ((U64)2 * reverse(binaryS)));
	U64 possibilitiesAntiDiagonal = ((pos->ocupied&antiDiagonalMasks8[(s /8) + 7 - (s%8)]) - ((U64)2 * binaryS)) ^ 
            reverse(reverse(pos->ocupied&antiDiagonalMasks8[(s /8) +7 - (s%8)]) - ((U64)2 * reverse(binaryS)));
	return (possibilitiesDiagonal&diagonalMasks8[(s/8) + (s%8)]) | (possibilitiesAntiDiagonal&antiDiagonalMasks8[(s /8) + 7 - (s %8)]);
}


void generateWPMoves(sPosition const *pos, sMoveList *list){
    if(pos->side==black){
        return;
    }

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
    if(pos->side==white){
        return;
    }
    
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

void generateNMoves(sPosition const *pos, sMoveList *list){
    U64 N=0;
    U64 NotMe=0;
    if(pos->side == white){
	    N = pos->bitboards[wN];
        NotMe = ~pos->allPieces[white];
    }else{
        N = pos->bitboards[bN];
        NotMe = ~pos->allPieces[black];
    }
	U64 NightMoves=N&~(N-(U64)1);
	U64 possibility=0;
	while(NightMoves != 0){
    	U64 index=trailingZero(NightMoves);
		if (index>18){
            possibility=knightSpanMask<<(index-(U64)18);
        }else{
            possibility=knightSpanMask>>((U64)18-index);
        }
        if (index%8<4){
            possibility &=~fileGHMask&NotMe;
        }else{
        	possibility &=~fileABMask&NotMe;
        }
        U64 move=possibility&~(possibility-(U64)1);
        while (move != 0){
            U64 toIndex=trailingZero(move);
            list->moves[list->count++].move = toMove(index, toIndex, 0, 0, 0);
            possibility&=~move;
            move=possibility&~(possibility-(U64)1);
        }
        N&=~NightMoves;
        NightMoves=N&~(N-1);
    }
}

void generateKMoves(sPosition const *pos, sMoveList *list){
    U64 N=0;
    U64 NotMe=0;
    if(pos->side == white){
	    N = pos->bitboards[wK];
        NotMe = ~pos->allPieces[white];
    }else{
        N = pos->bitboards[bK];
        NotMe = ~pos->allPieces[black];
    }
	U64 NightMoves=N&~(N-(U64)1);
	U64 possibility=0;
	while(NightMoves != 0){
    	U64 index=trailingZero(NightMoves);
		if (index>9){
            possibility=kingSpanMask<<(index-(U64)9);
        }else{
            possibility=kingSpanMask>>((U64)9-index);
        }
        if (index%8<4){
            possibility &=~fileGHMask&NotMe;
        }else{
        	possibility &=~fileABMask&NotMe;
        }
        U64 move=possibility&~(possibility-(U64)1);
        while (move != 0){
            U64 toIndex=trailingZero(move);
            list->moves[list->count++].move = toMove(index, toIndex, 0, 0, 0);
            possibility&=~move;
            move=possibility&~(possibility-(U64)1);
        }
        N&=~NightMoves;
        NightMoves=N&~(N-1);
    }
}

void generateBMoves(sPosition const *pos, sMoveList *list){
    U64 B=0;
    U64 NotMe=0;
    if(pos->side == white){
	    B = pos->bitboards[wB];
        NotMe = ~pos->allPieces[white];
    }else{
        B = pos->bitboards[bB];
        NotMe = ~pos->allPieces[black];
    }
    U64 i=B&~(B-(U64)1);
    U64 possibility=0;
    while(i != 0)
    {
        U64 iLocation=trailingZero(i);
        possibility=dAndAntiDMoves(iLocation, pos)&NotMe;
        printBitBoard(possibility);
        U64 j=possibility&~(possibility-(U64)1);
        while (j != 0)
        {
            U64 index=trailingZero(j);
            list->moves[list->count++].move = toMove(iLocation, index, 0, 0, 0);
            possibility&=~j;
            j=possibility&~(possibility-(U64)1);
        }
        B&=~i;
        i=B&~(B-1);
  }
}

void generateRMoves(sPosition const *pos, sMoveList *list){
    U64 B=0;
    U64 NotMe=0;
    if(pos->side == white){
	    B = pos->bitboards[wR];
        NotMe = ~pos->allPieces[white];
    }else{
        B = pos->bitboards[bR];
        NotMe = ~pos->allPieces[black];
    }
    U64 i=B&~(B-(U64)1);
    U64 possibility=0;
    while(i != 0)
    {
        U64 iLocation=trailingZero(i);
        possibility=hAndVMoves(iLocation, pos)&NotMe;
        printBitBoard(possibility);
        U64 j=possibility&~(possibility-(U64)1);
        while (j != 0)
        {
            U64 index=trailingZero(j);
            list->moves[list->count++].move = toMove(iLocation, index, 0, 0, 0);
            possibility&=~j;
            j=possibility&~(possibility-(U64)1);
        }
        B&=~i;
        i=B&~(B-1);
  }
}

void generateQMoves(sPosition const *pos, sMoveList *list){
    U64 B=0;
    U64 NotMe=0;
    if(pos->side == white){
	    B = pos->bitboards[wQ];
        NotMe = ~pos->allPieces[white];
    }else{
        B = pos->bitboards[bQ];
        NotMe = ~pos->allPieces[black];
    }
    U64 i=B&~(B-(U64)1);
    U64 possibility=0;
    while(i != 0)
    {
        U64 iLocation=trailingZero(i);
        possibility=hAndVMoves(iLocation, pos)&NotMe|dAndAntiDMoves(iLocation, pos)&NotMe;
        printBitBoard(possibility);
        U64 j=possibility&~(possibility-(U64)1);
        while (j != 0)
        {
            U64 index=trailingZero(j);
            list->moves[list->count++].move = toMove(iLocation, index, 0, 0, 0);
            possibility&=~j;
            j=possibility&~(possibility-(U64)1);
        }
        B&=~i;
        i=B&~(B-1);
  }
}

void generateAllMoves(sPosition const *pos, sMoveList *list){
    generateWPMoves(pos, list);
    generateBPMoves(pos, list);
    generateNMoves(pos, list);
    generateKMoves(pos, list);
    generateBMoves(pos, list);
    generateRMoves(pos, list);
    generateQMoves(pos, list);
}