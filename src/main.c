#include "defs.h"
#include "io.h"
#include "bitboards.h"
#include "board.h"
#include "movement.h"
#include "movegen.h"
#include "perft.h"



void init(sPosition *pos){
    initBitboards(pos);
}

int main(){
    sPosition pos[1];
    sMoveList list[1];

    init(pos);
    parseFen(pos, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    
    perftDivide(pos, 5);
    
    return 0;
}