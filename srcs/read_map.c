#include "wolf3d.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

static int	**malloc_map(int fd, char ***splited, int *rows, int *cols)
{
    char		*file;
    int			j;
    int     	**walls;

    file = read_file(fd);
    *splited = ft_strsplit(file, '\n');
    free(file);
    *rows = 0;
    *cols = 0;
    while ((*splited)[*rows])
    {
        j = ft_count_word((*splited)[(*rows)], ' ');
        if (++(*rows) == 1)
            *cols = j;
        else if (*cols != j)
			put_error(1);
    }
    if (*rows == 0)
		put_error(1);
    walls = (int **)ft_malloc_2d_array(*rows, *cols, sizeof(int));
    return (walls ? walls : 0);
}

static int      check_and_fill(int *wall, char *str, int *hero_pos)
{
    size_t  i;
    size_t  len;

    len = ft_strlen(str);
    i = 0;

    while (i < len)
    {
        if (!ft_isdigit(str[i]))
        {
            if (len == 1 && str[i] == 'X')
            {
				if (*hero_pos)
					put_error(2);
				else
					*hero_pos = 1;
				*wall = 0;
				return (1);
            }
            else
				put_error(1);
        }
        i++;
    }
    *wall = ft_atoi(str);
    return (0);
}

static int      check_full_map(t_map *map)
{
    int i;

    i = 0;
    while (i < map->cols)
    {
        if (map->walls[0][i] == 0 || map->walls[map->rows - 1][i] == 0)
			put_error(1);
        i++;
    }
    i = 0;
    while (i < map->rows)
    {
        if (map->walls[i][0] == 0 || map->walls[i][map->cols - 1] == 0)
			put_error(1);
        i++;
    }
    return (0);
}

static int		fill_map(t_map *map, char **table, t_hero *hero)
{
    int		i;
    int		j;
    char    **temp;
	int 	hero_pos;

	hero_pos = 0;
    i = -1;
    while (++i < map->rows)
    {
        j = -1;
        temp = ft_strsplit(table[i], ' ');
        while (++j < map->cols)
			if (check_and_fill(&map->walls[i][j], temp[j], &hero_pos) == 1)
				hero->pos = v2(j + 0.5, i + 0.5);
        ft_free_table(&temp, map->cols);
    }
	if (hero->pos.x == -1 && hero->pos.y == -1)
		put_error(2);
	check_full_map(map);
    return (0);
}

int				read_map(char *map_file, t_map *map, t_hero *hero)
{
    int     fd;
    char    **splited;

    fd = open(map_file, O_RDONLY);
    if (fd != -1) {
        map->walls = malloc_map(fd, &splited, &map->rows, &map->cols);
		printf("map (%d, %d)\n", map->rows, map->cols);
		hero->pos = v2(-1, -1);
        if (!map->walls || fill_map(map, splited, hero))
            exit(1);
        ft_free_table(&splited, map->rows);
        close(fd);
    }
    else
		put_error(1);
	return (0);
}