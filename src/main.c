#include "constants.h"
#include "bitboards.h"
#include "board.h"

sPosition pos;

void init(){
    initBitboards(&pos);
}

int main(){
    init();

    parseFen(&pos, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

    printBitBoard(pos.bitboards[wP]|pos.bitboards[wN]|pos.bitboards[wB]|pos.bitboards[wR]|pos.bitboards[wQ]|pos.bitboards[wK]|
        pos.bitboards[bP]|pos.bitboards[bN]|pos.bitboards[bB]|pos.bitboards[bR]|pos.bitboards[bQ]|pos.bitboards[bK]);
    
    return 0;
}