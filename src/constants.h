#ifndef CONSTANTS_H
#define CONSTANTS_H

/****************
    Includes
****************/
#include <stdio.h>
#include <stdlib.h>

/****************
    Macros
****************/
#define DEBUG

#ifndef DEBUG
#define ASSERT(n)
#else
#define ASSERT(n) \
if(!(n)) { \
printf("%s - Failed",#n); \
printf("On %s ",__DATE__); \
printf("At %s ",__TIME__); \
printf("In File %s ",__FILE__); \
printf("At Line %d\n",__LINE__); \
exit(1);\
}
#endif

/****************
    Type Defs
*****************/

//Unsigned 64 bit int
typedef unsigned long long U64;

/***********
    ENUMS
************/

//Square enums
enum{
    a8, b8, c8, d8, e8, f8, g8, h8,
    a7, b7, c7, d7, e7, f7, g7, h7,
    a6, b6, c6, d6, e6, f6, g6, h6,
    a5, b5, c5, d5, e5, f5, g5, h5,
    a4, b4, c4, d4, e4, f4, g4, h4,
    a3, b3, c3, d3, e3, f3, g3, h3,
    a2, b2, c2, d2, e2, f2, g2, h2,
    a1, b1, c1, d1, e1, f1, g1, h1, noSquare};

//File and Rank enums
enum { fileA, fileB, fileC, fileD, fileE, fileF, fileG, fileH, fileNone };
enum { rank1, rank2, rank3, rank4, rank5, rank6, rank7, rank8, rankNone };

//Piece enum
enum{empty, wP, wN, wB, wR, wQ, wK, bP, bN, bB, bR, bQ, bK};

//Color enum
enum{white, black};

//Castel perms enum
enum { wkCastle = 1, wqCastle = 2, bkCastle = 4, bqCastle = 8 };

//Boolean type
typedef enum {FALSE, TRUE} boolean;


/***************
    STRUCTS
****************/
typedef struct {
    U64 bitboards[13];
    U64 enPas;

    int side;
    int castlePerm;

} sPosition;
#endif