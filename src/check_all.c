#include "../Include/cub3D.h"

void check_extension(char *str)
{
	int len;
	char *aux;
	len = ft_strlen(str);
	if (len <= 4)
		error_msg("Error: name map invalid\n",NULL);
	aux = ft_substr(str,len - 4,len);
	if (ft_strncmp(aux,".cub",4) != 0)
	{
		free(aux);
		error_msg("Error: extension invalid\n",NULL);
	}
	free(aux);
}
void check_info(t_cub *game)
{
	if(game->north == NULL)
		error_msg("No set north\n",game);
	if(game->south == NULL)
		error_msg("No set south\n",game);
	if(game->west == NULL)
		error_msg("No set west\n",game);
	if(game->east == NULL)
		error_msg("No set east\n",game);
	if(game->floor == NULL)
		error_msg("No set floor\n",game);
	if(game->ceiling == NULL)
		error_msg("No set ceiling\n",game);
}

void ft_check_line(char *line,t_cub *game)
{
	if(!game->north && ft_strncmp(line,"NO ",3) == 0)
	{
		game->count_data++;
		game->north = ft_strdup(line + 3);
	}
	if(!game->south && ft_strncmp(line,"SO ",3) == 0)
	{
		game->count_data++;
		game->south = ft_strdup(line + 3);
	}
	if(!game->west && ft_strncmp(line,"WE ",3) == 0)
	{
		game->count_data++;
		game->west = ft_strdup(line + 3);
	}
	if(!game->east && ft_strncmp(line,"EA ",3) == 0)
	{
		game->count_data++;
		game->east = ft_strdup(line + 3);
	}
	if (!game->floor && ft_strncmp(line,"F ",2) == 0)
	{
		game->count_data++;
		game->floor = ft_strdup(line);
	}
	if (!game->ceiling && ft_strncmp(line,"C ",2) == 0)
	{
		game->count_data++;
		game->ceiling = ft_strdup(line);
	}
}
