#include <stdio.h>
#include <unistd.h>

#include "navy.h"
#include "data.h"

int init_game() {
    printf("my_pid: %d\n\n", getpid());
    printf("waiting for enemy...\n\n");
    pause();
    printf("enemy connected...\n");

    play_turn(1);
    return 0;
}
