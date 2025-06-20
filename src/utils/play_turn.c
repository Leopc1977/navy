#include <unistd.h>
#include <stdio.h>
#include <signal.h>

#include "navy.h"
#include "data.h"
#include "const.h"

void play_turn(int is_my_turn) {
    printf_maps();

    if (is_my_turn) {
        data->state = 2;
        data->target_succeded = -1;
        send_pos();
        pause();
        data->target_succeded = -1;
        if (data->has_won == 0) play_turn(0);
        return;
    }

    printf("waiting for ennemy's attack...\n");
    data->state = -1;

    while (data->target_line == -1 || data->target_col == -1) {
        pause();
    }
    printf("receive attack at %d %d\n", data->target_line, data->target_col);

    printf("received attack\n");
    if (data->player_map[data->target_line][data->target_col] > 0) {
        kill(data->ennemy_pid, SIGUSR1);
        usleep(1000);
        data->player_map[data->target_line][data->target_col] = BOAT_HIT;
    } else {
        kill(data->ennemy_pid, SIGUSR2);
        usleep(1000);
        data->player_map[data->target_line][data->target_col] = BOAT_MISS;
    }

    if (check_lose()) {
        kill(data->ennemy_pid, SIGUSR1);
        usleep(1000);
        return;
    } else {
        kill(data->ennemy_pid, SIGUSR2);
        usleep(1000);
    }

    data->target_col = -1;
    data->target_line = -1;

    play_turn(1);
}
