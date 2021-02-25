#ifndef PERFT_H
#define PERFT_H
#include "defs.h"
#include "movegen.h"
#include "movement.h"
#include "io.h"

extern int perft(sPosition *pos, int depth);
extern void perftDivide(sPosition *pos, int depth);

#endif