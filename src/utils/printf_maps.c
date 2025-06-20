#include <stdio.h>

#include "data.h"
#include "const.h"

void put_line(int *line)
{
    for (int a = 0; a < MAP_SIZE; a++) {
        int n = line[a];

        if (n == 0) {
            printf(".");
        } else if (n > 0) {
            printf("%d", n);
        } else if (n == BOAT_HIT) {
            printf("x");
        } else if (n == BOAT_MISS) {
            printf("o");
        }
        printf(" ");
    }
    printf("\n");
}

void map_display(int **map)
{
    printf(" |A B C D E F G H\n");
    printf("-+---------------\n");
    printf("1|"), put_line(map[0]);
    printf("2|"), put_line(map[1]);
    printf("3|"), put_line(map[2]);
    printf("4|"), put_line(map[3]);
    printf("5|"), put_line(map[4]);
    printf("6|"), put_line(map[5]);
    printf("7|"), put_line(map[6]);
    printf("8|"), put_line(map[7]);
}

void printf_maps(void) {
    printf("\nmy navy:\n");
    map_display(data->player_map);
    printf("\nenemy navy:\n");
    map_display(data->ennemy_map);
    printf("\n");
}
