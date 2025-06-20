#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "data.h"

int target_line = -1;
int target_col = -1;

void signal_handler(int sig, siginfo_t *siginfo, void *context) {
    (void)context;
    int state = data->state; // -1 = nothing, 0 = updating line pos, 1 = updating col pos, 2 = update hit/miss

    if (data->is_host && data->ennemy_pid == -1) {
        data->ennemy_pid = siginfo->si_pid;
    }

    if (sig == SIGUSR1) {
        state = state == -1 ? 0 : state;

        if (state == 0) {
            target_line++;
        } else if (state == 1) {
            target_col++;
        }
        else if (state == 2 && data->target_succeded != -1) {
            data->has_won = 1;
            state = -1;
        }

        data->target_succeded = 1;
        data->state = state;
    } else if (sig == SIGUSR2) {
        if (state == 0) {
            data->target_line = target_line;
            data->state = 1;
            target_line = -1;
        } else if (state == 1) {
            data->target_col = target_col;
            target_col = -1;       
        } else if (state == 2 && data->target_succeded != -1) {
            data->state = -1;
        }

        data->target_succeded = 0;
    }
}

int init_signal(void) {
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART | SA_SIGINFO;
    sa.sa_sigaction = signal_handler;

    if (sigaction(SIGUSR1, &sa, NULL) == -1) return 1;
    if (sigaction(SIGUSR2, &sa, NULL) == -1) return 1;
    return 0;
}
