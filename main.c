#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"

#define N_PLAYER 3
#define MAX_DIE  6

#define PLAYERSTATUS_LIVE 0
#define PLAYERSTATUS_END  1
#define PLAYERSTATUS_DIE  2

char player_name[N_PLAYER][10];
int  player_position[N_PLAYER];
int  player_coin[N_PLAYER];
int  player_status[N_PLAYER];

int rolldie(void) {
    return rand() % MAX_DIE + 1;
}

void printPlayerPosition(int p)
{
    int i;
    for (i = 0; i < N_BOARD; i++){
        printf("|");
        if (player_position[p] == i)
            printf("%c", player_name[p][0]);
        else if (board_getBoardStatus(i) == BOARDSTATUS_NOK)
            printf("X");
        else
            printf(" ");
    }
    printf("|\n");
}

void printPlayerStatus(void)
{
    int i;
    printf("--------------- PLAYER STATUS ---------------\n");
    for (i = 0; i < N_PLAYER; i++){
        printf("%s : pos %d | coin %d | ", player_name[i], player_position[i], player_coin[i]);

        if (player_status[i] == PLAYERSTATUS_LIVE)
            printf("LIVE\n");
        else if (player_status[i] == PLAYERSTATUS_END)
            printf("END\n");
        else
            printf("DIE\n");

        printPlayerPosition(i);
    }
    printf("---------------------------------------------\n");
}

void checkDie(void)
{
    int i;
    for (i = 0; i < N_PLAYER; i++){
        if (player_status[i] == PLAYERSTATUS_LIVE){
            if (board_getBoardStatus(player_position[i]) == BOARDSTATUS_NOK){
                player_status[i] = PLAYERSTATUS_DIE;
                printf("%s is DEAD by the shark!\n", player_name[i]);
            }
        }
    }
}

int getAlivePlayer(void)
{
    int i;
    int cnt = 0;
    for (i = 0; i < N_PLAYER; i++){
        if (player_status[i] == PLAYERSTATUS_END)
            cnt++;
    }
    return cnt;
}

int getWinner(void)
{
    int i;
    int winner = -1;
    int max_coin = -1;

    for (i = 0; i < N_PLAYER; i++){
        if (player_status[i] != PLAYERSTATUS_DIE){
            if (player_coin[i] > max_coin){
                max_coin = player_coin[i];
                winner = i;
            }
        }
    }
    return winner;
}

int game_end(void)
{
    int i;
    for (i = 0; i < N_PLAYER; i++){
        if (player_status[i] == PLAYERSTATUS_LIVE)
            return 0;
    }
    return 1;
}

int main(void)
{
    int turn = 0;
    int i;
    int p;
    int die;
    int c;

    srand((unsigned)time(NULL));

    printf("=====================================\n");
    printf("============ SHARK GAME ============\n");
    printf("=====================================\n");

    board_initBoard();

    for (i = 0; i < N_PLAYER; i++){
        printf("Enter player %d name: ", i + 1);
        scanf("%s", player_name[i]);
        player_position[i] = 0;
        player_coin[i] = 0;
        player_status[i] = PLAYERSTATUS_LIVE;
    }

    while (!game_end()){
        p = turn % N_PLAYER;

        if (player_status[p] != PLAYERSTATUS_LIVE){
            turn++;
            continue;
        }

        printf("\n------- %s's TURN -------\n", player_name[p]);
        board_printBoardStatus();
        printPlayerStatus();

        printf("Press ENTER to roll a die...");
        getchar();
        getchar();

        die = rolldie();
        printf("Die result: %d\n", die);

        player_position[p] += die;

        if (player_position[p] >= N_BOARD - 1){
            player_position[p] = N_BOARD - 1;
            player_status[p] = PLAYERSTATUS_END;
            printf("%s reached the end!\n", player_name[p]);
        }

        c = board_getBoardCoin(player_position[p]);
        if (c > 0){
            player_coin[p] += c;
            printf("%s got %d coins!\n", player_name[p], c);
        }

        turn++;

        if (turn % N_PLAYER == 0){
            printf("\n=== SHARK MOVES ===\n");
            board_stepShark();
            checkDie();
        }
    }

    printf("\n=============== GAME OVER ===============\n");

    i = getWinner();
    printf("Winner : %s (coin %d)\n", player_name[i], player_coin[i]);

    return 0;
}
