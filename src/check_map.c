#include "../Include/cub3D.h"

void check_valid_position_player(char **map,t_cub *game)
{
	if (game->y == 0 || game->x == 0)
		error_msg("Error invalid player position\n",game);
	if ((map[(int)game->y][(int)game->x - 1] == '\0') || (map[(int)game->y][(int)game->x + 1] == '\0')
		|| (!map[(int)game->y + 1] || map[(int)game->y + 1][(int)game->x] == '\0') || ( map[(int)game->y - 1][(int)game->x] == '\0'))
		error_msg("Error null around player position\n",game);
	if ((map[(int)game->y][(int)game->x - 1] == ' ') || (map[(int)game->y][(int)game->x + 1] == ' ')
		|| (map[(int)game->y + 1][(int)game->x] == ' ') || (map[(int)game->y - 1][(int)game->x] == ' '))
		error_msg("Error spaces around player position\n",game);
	if ((map[(int)game->y][(int)game->x - 1] == '\n') || (map[(int)game->y][(int)game->x + 1] == '\n')
		|| (map[(int)game->y + 1][(int)game->x] == '\n') || (map[(int)game->y - 1][(int)game->x] == '\n'))
		error_msg("Error new line around player position\n",game);	
}

void check_caracter_map(char **map,t_cub *game)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != 'N'
			&& map[i][j] != 'S' && map[i][j] != 'W' && map[i][j] != '\n'
			&& map[i][j] != 'E' && map[i][j] != ' ')
				error_msg("Error character invalid in map\n",game);
			if(map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W')
				save_player(map[i][j],i,j,game);
			j++;
		}
		i++;
	}
	if(game->player != 1)
		error_msg("Invalid number players\n",game);
}

void check_map(char **map,t_cub *game)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if (map[i][0] == '0')
				error_msg("Error zero first caracter\n",game);
			if (map[i][j] == '0' && (i == 0 || (map[i][j - 1] == '\0') || (map[i][j + 1] == '\0')
				|| (!map[i + 1] || map[i + 1][j] == '\0') || ( map[i - 1][j] == '\0')))
				error_msg("Error null around zero\n",game);
			if (map[i][j] == '0' && ((map[i][j - 1] == ' ') || (map[i][j + 1] == ' ')
				|| (map[i + 1][j] == ' ') || (map[i - 1][j] == ' ')))
				error_msg("Error spaces around zero\n",game);
			if (map[i][j] == '0' && ((map[i][j - 1] == '\n') || (map[i][j + 1] == '\n')
				|| (map[i + 1][j] == '\n') || (map[i - 1][j] == '\n')))
				error_msg("Error new line around zero\n",game);
			j++;
		}
		i++;
	}
}
