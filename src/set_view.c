#include "../Include/cub3D.h"

double set_view(t_cub *game)
{
	if (game->player_view == 'E')
		return(0);
	else if(game->player_view == 'N')
		return(M_PI_2 + M_PI);
	else if(game->player_view == 'W')
		return(M_PI);
	else
		return(M_PI_2);
}