#include "wolf3d.h"
#include "libft.h"

int	main(int argc, char **argv)
{
	if (argc != 2)
		ft_puterror("Usage: wolf3d map_name.map");
	else
		wolf3d(argv[1]);
}