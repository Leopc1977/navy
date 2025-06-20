#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

#include "navy.h"
#include "data.h"

t_data *data = NULL;

t_data *init_data(int ac, char **av) {
    data = malloc(sizeof(t_data));
    if (data == NULL) return NULL;

    int is_host = ac == 2;

    data->player_pid = getpid();
    data->ennemy_pid = -1;
    data->target_line = -1;
    data->target_col = -1;
    data->target_succeded = -1;
    data->has_won = 0;
    data->state = -2;

    if (is_host) {
        if (init_map(av[1]) == 1) return NULL;
    } else if (!is_host) {
        data->ennemy_pid = atoi(av[1]);
        if (init_map(av[2]) == 1) return NULL;
    }

    data->is_host = is_host;

    if (init_signal() == 1) return NULL;

    return data;
}
