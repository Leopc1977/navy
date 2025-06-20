#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

#include "navy.h"
#include "data.h"

int join_game() {
    printf("my_pid: %d\n\n", getpid());
    kill(data->ennemy_pid, SIGUSR1);
    usleep(1000);
    printf("successfully connected...\n");

    play_turn(0);

    return 0;
}
