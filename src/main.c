#include "defs.h"
#include "io.h"
#include "bitboards.h"
#include "board.h"
#include "movement.h"
#include "movegen.h"

sPosition pos;
sMoveList list;

void init(){
    initBitboards(&pos);
}

int main(){
    init();
    parseFen(&pos, "7K/8/8/8/8/3pP3/2p5/1Q1R3K w - e2 0 1");
    generateBPMoves(&pos, &list);

    printBoard(&pos);

    for(int i = 0; i < list.count; i++){
        printf("Move %s\n", moveToString(list.moves[i].move));
    }

    printf("\nWhite Material = %d\nBlack Material = %d\nTotal Score = %d\n", pos.material[white], pos.material[black], pos.material[white]-pos.material[black]);
    
    return 0;
}