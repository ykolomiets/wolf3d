#ifndef MAP_H
# define MAP_H

# include "camera.h"

typedef struct  s_map
{
    int     rows;
    int     cols;
    int     **walls;
}               t_map;

int             read_map(char *file, t_map *map, t_camera *cam);

#endif
