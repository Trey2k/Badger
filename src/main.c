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
    parseFen(&pos, "rnbqkbnr/ppp3pp/8/8/8/8/8/RNBQKBNR w KQkq - 0 1");
    generateAllMoves(&pos, &list);

    printBoard(&pos);

    for(int i = 0; i < list.count; i++){
        printf("Move %s\n", moveToString(list.moves[i].move));
    }

    printf("\nWhite Material = %d\nBlack Material = %d\nTotal Score = %d\n", pos.material[white], pos.material[black], pos.material[white]-pos.material[black]);
    
    return 0;
}