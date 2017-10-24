#include "wolf3d.h"
#include "libft.h"
#include <stdlib.h>

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putendl("Usage: wolf3d map_name.map");
		exit(1);
	}
	else
		wolf3d(argv[1]);
}