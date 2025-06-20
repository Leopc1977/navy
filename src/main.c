#include <stdlib.h>
#include <stdio.h>

#include "navy.h"
#include "data.h"

int main(int ac, char **av)
{
    int return_value = 0;

    if (check_args(ac, av) == 1) return 1;

    if (init_data(ac, av) == NULL) return 1;

    if (ac == 2) return_value = init_game();
    else if (ac == 3) return_value = join_game();
    
    printf("%s\n", data->has_won ? "I won" : "Enemy won");

    free_data();

    return return_value;
}
