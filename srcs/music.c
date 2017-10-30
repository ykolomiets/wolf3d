#include "wolf3d.h"
#include <stdlib.h>

void 	music_on()
{
	system("pkill afplay");
	system("afplay resources/main.mp3 &");
}

void	music_off()
{
	system("pkill afplay");;
}