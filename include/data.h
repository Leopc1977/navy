#ifndef DATA_H_
#define DATA_H_

#include <stdbool.h>
#include <stdint.h>

#define MAP_SIZE 8

typedef struct s_data {
    int **player_map;
    int **ennemy_map;
    int is_host;

    int player_pid;
    int ennemy_pid;

    int target_line;
    int target_col;

    int target_succeded;
    int has_won;

    int state;
} t_data;

extern t_data *data;

#endif /* DATA_H_ */
