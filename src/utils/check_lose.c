#include "data.h"

int check_lose() {
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            if (data->player_map[i][j] > 0)
                return 0;
        }
    }
    return 1;
}
