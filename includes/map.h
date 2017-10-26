#ifndef MAP_H
# define MAP_H

# include "hero.h"

typedef struct  s_map
{
    int     rows;
    int     cols;
    int     **walls;
}               t_map;

int             read_map(char *file, t_map *map, t_hero *hero);

#endif
