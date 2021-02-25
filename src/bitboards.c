#include "bitboards.h"

//Init the bitboards to 0 values
void initBitboards(sPosition *pos){
    for(int i = 0; i < 12; i++){
        pos->bitboards[i] = (U64)0;
    }
}

void removeFromBitboard(U64 *bitboard, int sq){
    *bitboard &= ~((U64)1 << sq);
}

void addToBitboard(U64 *bitboard, int sq){
    *bitboard |= (U64)1 << sq;
}

int countBits(U64 bitboard) {
  int r;
  for(r = 0; bitboard; r++, bitboard &= bitboard - 1);
  return r;
}

int trailingZero(U64 bitboard) { 
  int count = 0; 
  while ((bitboard & 1) == 0) 
  { 
      bitboard = bitboard >> 1; 
      count++; 
  } 
  return count; 
} 

int getPieceAtSquare(sPosition const *pos, int sq){
    for(int i = wP; i <= bK; i++){
        if(((U64)1 << sq) & pos->bitboards[i]){
            return i;
        }
    }
    return empty;
}

void printBitBoard(U64 bitboard) {
	printf("   ________________________\n");
    for(int rank = rank8; rank >= rank1; rank--) {
        printf("%d |", rank+1);
        for(int file = fileA; file <= fileH; file++) {
			int sq = fileRankToSquare(file, rank);
			if(((U64)1 << sq) & bitboard){ 
				printf(" X ");
            }else{ 
				printf(" - ");
            }
		}
		printf("|\n");
	}  
    printf("  |________________________|\n");
    printf("    A  B  C  D  E  F  G  H\n");
}