#include "bitboards.h"

//Init the bitboards to 0 values
void initBitboards(sPosition *pos){
    for(int i = 0; i < 12; i++){
        pos->bitboards[i] = (U64)0;
    }
}

void addToBitboard(U64 *bitboard, int sq){
    *bitboard |= (U64)1 << sq;
}

void printBitBoard(U64 bb) {
	printf("\n");
    for(int rank = rank8; rank >= rank1; rank--) {
        printf("%d ", rank+1);
        for(int file = fileA; file <= fileH; file++) {
			int sq = fileRankToSquare[file][rank];
			if(((U64)1 << sq) & bb){ 
				printf(" X ");
            }else{ 
				printf(" - ");
            }
		}
		printf("\n");
	}  
    printf("   A  B  C  D  E  F  G  H\n");
}