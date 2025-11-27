#ifndef __BOARD_H__
#define __BOARD_H__

#include <stdio.h>
#include <stdlib.h>

#define N_BOARD         20
#define BOARDSTATUS_OK  1
#define BOARDSTATUS_NOK 0

#define N_COINPOS       12
#define MAX_COIN        4

#define SHARK_INITPOS   0
#define MAX_SHARKSTEP   4

void board_initBoard(void);
int  board_getBoardStatus(int pos);
int  board_getBoardCoin(int pos);
int  board_getSharkPosition(void);
int  board_stepShark(void);
void board_printBoardStatus(void);

#endif
