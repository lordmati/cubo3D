#include "../Include/cub3D.h"

static void free_struc(t_cub *game)
{
	if(game->north)
		free(game->north);
	if(game->south)
		free(game->south);
	if(game->west)
		free(game->west);
	if(game->east)
		free(game->east);
	if(game->floor)
		free(game->floor);
	if(game->ceiling)
		free(game->ceiling);
	if(game->arr_ceiling)
		free(game->arr_ceiling);
	if(game->arr_floor)
		free(game->arr_floor);
	if(game->map)
		free_matrix(game->map);
	return;
}

void error_msg(char *str,t_cub *game)
{
	if (game)
		free_struc(game);
	ft_putstr_fd(str,2);
	exit(1);
}