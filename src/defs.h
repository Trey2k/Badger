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
exit(1); \
}
#endif

/************
    CONSTS
*************/

#define maxPositionMoves 218
#define maxGameMoves 2048

#define pawnValue 100
#define knightValue 325
#define bishopValue 325
#define rookValue 550
#define queenValue 1000

//EnPas movement flag
#define moveFlagEP 0x40000

//Pawnstart movement flag
#define moveFlagPS 0x80000

//Castel movement flag
#define moveFlagCA 0x1000000

//Capture movement flag
#define moveFlagCAP 0x7C000

//Promotion flag movement flag
#define moveFlagPROM 0xF00000

#define fileAMask 0x101010101010101ull
#define fileHMask 0x8080808080808080ull
#define fileABMask 0x303030303030303ull
#define fileGHMask 0xC0C0C0C0C0C0C0C0ull
#define rank1Mask 0xFFull
#define rank4Mask 0xFF000000ull
#define rank5Mask 0xFF00000000ull
#define rank8Mask 0xFF00000000000000ull

#define knightSpanMask 0xA1100110Aull
#define kingSpanMask 0x70507ull


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
    a1, b1, c1, d1, e1, f1, g1, h1,
    a2, b2, c2, d2, e2, f2, g2, h2,
    a3, b3, c3, d3, e3, f3, g3, h3,
    a4, b4, c4, d4, e4, f4, g4, h4,
    a5, b5, c5, d5, e5, f5, g5, h5,
    a6, b6, c6, d6, e6, f6, g6, h6,
    a7, b7, c7, d7, e7, f7, g7, h7,
    a8, b8, c8, d8, e8, f8, g8, h8, noSquare};

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

typedef struct{
    U64 enPas;

    int move;
    int castlePerms;
    int fiftyMove;

} sHistory;

typedef struct {
    U64 bitboards[13];
    U64 allPieces[2];

    U64 ocupied;
    U64 empty;
    U64 enPas;

    int material[2];

    int side;
    int castlePerms;
    int fiftyMove;
    int ply;
    int hisPly;

    sHistory history[maxGameMoves];

} sPosition;

#endif