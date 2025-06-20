#include <stdlib.h>

#include "data.h"

void free_data() {
    if (!data) return;

    if (data->player_map) {
        for (int i = 0; i < MAP_SIZE; i++)
            free(data->player_map[i]);
        free(data->player_map);
    }
    
    if (data->ennemy_map) {
        for (int i = 0; i < MAP_SIZE; i++)
            free(data->ennemy_map[i]);
        free(data->ennemy_map);
    }
    
    free(data);
}
