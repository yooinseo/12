#include "board.h"

static int board_status[N_BOARD];
static int board_coin[N_BOARD];
static int shark_position;

void board_printBoardStatus(void)
{
    int i;
    printf("--------------- BOARD STATUS ---------------\n");
    for (i = 0; i < N_BOARD; i++){
        printf("|");
        if (board_status[i] == BOARDSTATUS_NOK)
            printf("X");
        else
            printf("O");
    }
    printf("|\n");
    printf("--------------------------------------------\n");

    printf("--------------- BOARD COIN -----------------\n");
    for (i = 0; i < N_BOARD; i++)
        printf("|%d", board_coin[i]);
    printf("|\n");
    printf("--------------------------------------------\n");

    printf("Shark Position : %d\n", shark_position);
}

int board_getBoardStatus(int pos)
{
    return board_status[pos];
}

int board_getBoardCoin(int pos)
{
    int coin = board_coin[pos];
    board_coin[pos] = 0;
    return coin;
}

int board_getSharkPosition(void)
{
    return shark_position;
}

int board_stepShark(void)
{
    int step = rand() % MAX_SHARKSTEP + 1;
    int i;

    for (i = 0; i < step; i++){
        if (shark_position + 1 >= N_BOARD) break;
        shark_position++;
        board_status[shark_position] = BOARDSTATUS_NOK;
    }
    return shark_position;
}

void board_initBoard(void)
{
    int i;

    for (i = 0; i < N_BOARD; i++){
        board_status[i] = BOARDSTATUS_OK;
        board_coin[i] = 0;
    }

    shark_position = SHARK_INITPOS;

    for (i = 0; i < N_COINPOS; i++){
        int flag = 0;
        while (!flag){
            int pos = rand() % N_BOARD;
            if (board_coin[pos] == 0){
                board_coin[pos] = rand() % MAX_COIN + 1;
                flag = 1;
            }
        }
    }
}
