#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#include "data.h"
#include "const.h"

void send_pos(void) {
    char *line = NULL;
    size_t len = 0;
    int target_line, target_col;

    printf("attack: ");

    if (getline(&line, &len, stdin) == - 1) {
        send_pos();
        printf("\nwrong position\n\n");
        return;
    } else if (line[0] == '\n') {
        printf("\nwrong position\n\n");
        send_pos();
        return;
    }
    printf("\n");

    target_col = (line[0] - 'A');
    target_line = (line[1] - '0' - 1);

    for (int i = 0; i < target_line + 1; i++) {
        kill(data->ennemy_pid, SIGUSR1);
        usleep(1000);
    }

    kill(data->ennemy_pid, SIGUSR2);
    usleep(1000);
    for (int i = 0; i < target_col + 1; i++) {
        kill(data->ennemy_pid, SIGUSR1);
        usleep(1000);
    }
    kill(data->ennemy_pid, SIGUSR2);
    usleep(1000);

    printf("result: %c%c: ", line[0], line[1]);
    if (data->target_succeded) {
        data->ennemy_map[target_line][target_col] = BOAT_HIT;
        printf("hit\n");
    } else {
        data->ennemy_map[target_line][target_col] = BOAT_MISS;
        printf("missed\n");
    }
}
