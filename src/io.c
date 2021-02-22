#include "io.h"
#include <stdio.h>

char *squareToString(const int sq) {
    static char SqStr[3];
	int file = sq & 7; //9 & 7 = 1; 16 & 7 = 0 
	int rank = sq >> 3; //9 >> 3 = 1; 16 >> 3 = 2
	sprintf(SqStr, "%c%c", ('a' + file), ('1' + rank));
    return SqStr;
}

char *moveToString(const int move) {
    static char MvStr[6];
	int fileFrom = getFrom(move) & 7; 
	int rankFrom = getFrom(move) >> 3;

    int fileTo = getTo(move) & 7; 
	int rankTo = getTo(move) >> 3;

    int promoted = getPromoted(move);

    if(promoted) {
		char pchar = 'q';
		if(promoted == wN || promoted == bN) {
			pchar = 'n';
		} else if(promoted == wR || promoted == bR)  {
			pchar = 'r';
		} else if(promoted == wB || promoted == bB)  {
			pchar = 'b';
		}
		sprintf(MvStr, "%c%c%c%c%c", ('a'+fileFrom), ('1'+rankFrom), ('a'+fileTo), ('1'+rankTo), pchar);
	} else {
		sprintf(MvStr, "%c%c%c%c", ('a'+fileFrom), ('1'+rankFrom), ('a'+fileTo), ('1'+rankTo));
	}
    return MvStr;
}

char pieceToChar(const int piece) {
    switch (piece)
    {
    case wP:
        return 'P';
    case wN:
        return 'N';
    case wB:
        return 'B';
    case wR:
        return 'R';
    case wQ:
        return 'Q';
    case wK:
        return 'K';

    case bP:
        return 'p';
    case bN:
        return 'n';
    case bB:
        return 'b';
    case bR:
        return 'r';
    case bQ:
        return 'q';
    case bK:
        return 'k';

    default:
        return '-';
    }
}

void printBoard(sPosition *pos){
    printf("\n   ________________________\n");
    for(int rank = rank8; rank >= rank1; rank--) {
        printf("%d |", rank+1);
        for(int file = fileA; file <= fileH; file++) {
			int sq = fileRankToSquare(file, rank);
			printf(" %c ", pieceToChar(getPieceAtSquare(pos, sq)));
		}
		printf("|\n");
	}  
    printf("  |________________________|\n");
    printf("    A  B  C  D  E  F  G  H\n");
}