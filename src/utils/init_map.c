#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>

#include "navy.h"
#include "data.h"

void add_boat_to_map(int boat_len, char *first_pos, char *last_pos) {
    int first_pos_col = first_pos[0] - 'A'; 
    int first_pos_line = first_pos[1] - '0' - 1;
    int last_pos_col = last_pos[0] - 'A'; 
    int last_pos_line = last_pos[1] - '0' - 1;

    if (
        (first_pos_col == last_pos_col && first_pos_line == last_pos_line)
        ||
        (first_pos_col != last_pos_col && first_pos_line != last_pos_line)
    ) {
        perror("incorrect pos");
    }
    if (first_pos_col != last_pos_col) {
        int dir = first_pos_col < last_pos_col ? 1 : -1;
        for (int i = 0; i < boat_len; i++) data->player_map[first_pos_line][first_pos_col + i * dir] = boat_len;
    } else {
        int dir = first_pos_line < last_pos_line ? 1 : -1;
        for (int i = 0; i < boat_len; i++) data->player_map[first_pos_line + i * dir][first_pos_col] = boat_len;
    }
}

int init_map(char *filepath) {
    data->player_map = malloc(sizeof(int *) * (MAP_SIZE));
    if (data->player_map == NULL) return 1;

    for (int l = 0; l < MAP_SIZE; l++) {
        data->player_map[l] = malloc(sizeof(int) * (MAP_SIZE));
        if (data->player_map[l] == NULL) return 1;
        for (int c = 0; c < MAP_SIZE; c++)
            data->player_map[l][c] = 0;
    }

    data->ennemy_map = malloc(sizeof(int *) * (MAP_SIZE));
    if (data->ennemy_map == NULL) return 1;
    for (int l = 0; l < MAP_SIZE; l++) {
        data->ennemy_map[l] = malloc(sizeof(int) * (MAP_SIZE));
        if (data->ennemy_map[l] == NULL) return 1;
        for (int c = 0; c < MAP_SIZE; c++)
            data->ennemy_map[l][c] = 0;
    }

    FILE *file;
    struct stat infos;
    char *buffer;

    if (stat(filepath, &infos) != 0) {
        perror("Erreur avec stat");
        return 1;
    }

    file = fopen(filepath, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    buffer = malloc(infos.st_size + 1);
    if (buffer == NULL) {
        perror("Erreur d'allocation mémoire");
        fclose(file);
        return 1;
    }

    size_t lus = fread(buffer, 1, infos.st_size, file);
    buffer[lus] = '\0';

    char *sep_line = "\n";
    char *line, *line_brkt;

    for (line = strtok_r(buffer, sep_line, &line_brkt);
        line;
        line = strtok_r(NULL, sep_line, &line_brkt)) {
        char *sep_pos = ":";
        char *pos, *pos_brkt;
        int i = 0;
        int boat_len = 0;
        char *first_pos, *last_pos;

        for (pos = strtok_r(line, sep_pos, &pos_brkt);
            pos;
            pos = strtok_r(NULL, sep_pos, &pos_brkt)) {
                if (i == 0) {
                    boat_len = atoi(pos);
                } else if (i == 1) {
                    first_pos = malloc(strlen(pos) + 1);
                    strcpy(first_pos, pos);
                } else if (i == 2) {
                    last_pos = malloc(strlen(pos) + 1);
                    strcpy(last_pos, pos);
                }
                i++;
        }

        add_boat_to_map(boat_len, first_pos, last_pos);

        free(first_pos);
        free(last_pos);
    }

    free(buffer);
    fclose(file);

    return 0;
}
