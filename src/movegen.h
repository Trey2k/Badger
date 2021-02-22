#ifndef MOVEGEN_H
#define MOVEGEN_H

#include "defs.h"
#include "movement.h"

extern void generateWPMoves(sPosition const *pos, sMoveList *list);
extern void generateBPMoves(sPosition const *pos, sMoveList *list);
#endif

