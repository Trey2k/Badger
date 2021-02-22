#include "board.h"

int inline fileRankToSquare(int file, int rank){
    return 8*rank+file;
}

void resetBoard(sPosition *pos){
    pos->enPas = 0;
    pos->castlePerms=0;
    pos->side=white;
    
    for(int i = empty; i <= bK; i++){
        pos->bitboards[i] = 0;
    }
}

void updatePosition(sPosition *pos){
    pos->material[white] = 0;
    pos->material[black] = 0;

    pos->material[white] += countBits(pos->bitboards[wP]) * pawnValue;
    pos->material[black] += countBits(pos->bitboards[bP]) * pawnValue;

    pos->material[white] += countBits(pos->bitboards[wN]) * knightValue;
    pos->material[black] += countBits(pos->bitboards[bN]) * knightValue;

    pos->material[white] += countBits(pos->bitboards[wB]) * bishopValue;
    pos->material[black] += countBits(pos->bitboards[bB]) * bishopValue;

    pos->material[white] += countBits(pos->bitboards[wR]) * rookValue;
    pos->material[black] += countBits(pos->bitboards[bR]) * rookValue;

    pos->material[white] += countBits(pos->bitboards[wQ]) * queenValue;
    pos->material[black] += countBits(pos->bitboards[bQ]) * queenValue;

    pos->allPieces[white] = pos->bitboards[wP]|pos->bitboards[wN]|pos->bitboards[wB]|pos->bitboards[wR]|pos->bitboards[wQ]|pos->bitboards[wK];
    pos->allPieces[black] = pos->bitboards[bP]|pos->bitboards[bN]|pos->bitboards[bB]|pos->bitboards[bR]|pos->bitboards[bQ]|pos->bitboards[bK];

    pos->ocupied = pos->allPieces[white]|pos->allPieces[black];
    pos->empty = ~pos->ocupied;
}

boolean parseFen(sPosition *pos, char *fen) {

	ASSERT(fen!=NULL);
	ASSERT(pos!=NULL);
    int  rank = rank8;
    int  file = fileA;
	resetBoard(pos);

	while ((rank >= rank1) && *fen) {
        int  piece = 0;
	    int count = 1;
		switch (*fen) {
            case 'p': piece = bP; break;
            case 'r': piece = bR; break;
            case 'n': piece = bN; break;
            case 'b': piece = bB; break;
            case 'k': piece = bK; break;
            case 'q': piece = bQ; break;
            case 'P': piece = wP; break;
            case 'R': piece = wR; break;
            case 'N': piece = wN; break;
            case 'B': piece = wB; break;
            case 'K': piece = wK; break;
            case 'Q': piece = wQ; break;

            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
                piece = empty;
                count = *fen - '0';
                break;

            case '/':
            case ' ':
                rank--;
                file = fileA;
                fen++;
                continue;

            default:
                printf("FEN error \n");
                return FALSE;
        }

		for (int i = 0; i < count; i++) {
            if(piece != empty){
                int sq = fileRankToSquare(file, rank);
                addToBitboard(&pos->bitboards[piece], sq);
            }
            file++;
        }
		fen++;
	}

	ASSERT(*fen == 'w' || *fen == 'b');

    if(*fen == 'w'){
        pos->side = white;
    }else{
        pos->side = black;
    }
	
	fen += 2;

	for (int i = 0; i < 4; i++) {
        if (*fen == ' ') {
            break;
        }
		switch(*fen) {
			case 'K': pos->castlePerms |= wkCastle; break;
			case 'Q': pos->castlePerms |= wqCastle; break;
			case 'k': pos->castlePerms |= bkCastle; break;
			case 'q': pos->castlePerms |= bqCastle; break;
			default: break;
        }
		fen++;
	}
	fen++;

	ASSERT(pos->castlePerms>=0 && pos->castlePerms <= 15);

	if (*fen != '-') {
        int file, rank = 0;
		file = fen[0] - 'a';
		rank = fen[1] - '1';
        fen+=3;

		ASSERT(file>=fileA && file <= fileH);
		ASSERT(rank>=rank1 && rank <= rank8);
		addToBitboard(&pos->enPas, fileRankToSquare(file, rank));
    }else{
        fen+=2;
    }

	//pos->posKey = GeneratePosKey(pos);

	updatePosition(pos);

	return TRUE;
}

U64 inline allBoards(sPosition *pos){
    return pos->bitboards[wP]|pos->bitboards[wN]|pos->bitboards[wB]|pos->bitboards[wR]|pos->bitboards[wQ]|pos->bitboards[wK]|
        pos->bitboards[bP]|pos->bitboards[bN]|pos->bitboards[bB]|pos->bitboards[bR]|pos->bitboards[bQ]|pos->bitboards[bK];
}