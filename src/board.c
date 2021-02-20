#include "board.h"

const int fileRankToSquare[8][8] = {
    {a1, a2, a3, a4, a5, a6, a7, a8},
    {b1, b2, b3, b4, b5, b6, b7, b8},
    {c1, c2, c3, c4, c5, c6, c7, c8},
    {d1, d2, d3, d4, d5, d6, d7, d8},
    {e1, e2, e3, e4, e5, e6, e7, e8},
    {f1, f2, f3, f4, f5, f6, f7, f8},
    {g1, g2, g3, g4, g5, g6, g7, g8},
    {h1, h2, h3, h4, h5, h6, h7, h8}};

int parseFen(sPosition *pos, char *fen) {

	ASSERT(fen!=NULL);
	ASSERT(pos!=NULL);
    int boardindex = 0;
    

	//ResetBoard(pos);

	while ((boardindex < 64) && *fen) {
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
                fen++;
                continue;

            default:
                printf("FEN error \n");
                return 0;
        }

		for (int i = 0; i < count; i++) {
            int sq = boardindex++;
            addToBitboard(&pos->bitboards[piece], sq);
        }
		fen++;
	}
    fen++;
    
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
			case 'K': pos->castlePerm |= wkCastle; break;
			case 'Q': pos->castlePerm |= wqCastle; break;
			case 'k': pos->castlePerm |= bkCastle; break;
			case 'q': pos->castlePerm |= bqCastle; break;
			default: break;
        }
		fen++;
	}
	fen++;

	ASSERT(pos->castlePerm>=0 && pos->castlePerm <= 15);

	if (*fen != '-') {
        int file, rank = 0;
		file = fen[0] - 'a';
		rank = fen[1] - '1';

		ASSERT(file>=fileA && file <= fileH);
		ASSERT(rank>=rank1 && rank <= rank8);

		addToBitboard(&pos->enPas, fileRankToSquare[file][rank]);
    }

	//pos->posKey = GeneratePosKey(pos);

	//UpdateListsMaterial(pos);

	return 1;
}