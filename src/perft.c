#include "perft.h"
#include "time.h"
#include "misc.h"

int perft(sPosition *pos, int depth){
    if(depth==0){
        return 1;
    }
    int leafNodes = 0;
    sMoveList list[1];

    generateAllMoves(pos, list);

    for(int i = 0; i < list->count; i++){
        if(!makeMove(pos, list->moves[i].move)){
            continue;
        }

        leafNodes += perft(pos, depth-1);
        undoMove(pos);
    }

    return leafNodes;
}

void perftDivide(sPosition *pos, int depth){
    int leafNodes = 0;
    sMoveList list[1];

    printBoard(pos, "Current Position");

    int start = getTimeMs();

    generateAllMoves(pos, list);

    for(int i = 0; i < list->count; i++){
        int tmpNodes = 0;
        if(!makeMove(pos, list->moves[i].move)){
            continue;
        }

        tmpNodes = perft(pos, depth-1);
        printf("%s: %d\n", moveToString(list->moves[i].move), tmpNodes);
        leafNodes += tmpNodes;
        undoMove(pos);
    }

    int stop = getTimeMs();

    printf("\nPerft finished\nNodes: %d\nCalculation time: %dMs\n", leafNodes, stop - start);
}