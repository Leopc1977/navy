#ifndef NAVY_H_
#define NAVY_H_

#include "data.h"

int check_args(int ac, char **av);
t_data *init_data(int ac, char **av);
int init_signal(void);
int init_game();
int join_game();
void play_turn(int is_my_turn);
void free_data();
int init_map(char *filepath);
void send_pos(void);
void printf_maps(void);
int check_lose();

#endif
