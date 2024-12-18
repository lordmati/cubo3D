#include "../Include/cub3D.h"

void save_player(char c,int y,int x,t_cub *game)
{
	game->player_view = c;
	game->y = y + 0.5;
	game->x = x + 0.5;
	game->player++;
}
void save_map(t_cub *game,char *file,int i, int j)
{
	int fd;
	char *line;

	fd = open(file,O_RDONLY);
	line = ft_strdup("");
	game->map = (char **)malloc(sizeof(char *) * (game->count_map));
	if (!game->map)
		error_msg("Error allocated malloc\n",game);
	while(line)
	{
		free(line);
		line = get_next_line(fd);
		if (line)
		{
			if (i == game->count_line + 1)
			{
				game->map[j] = ft_strdup(line);
				j++;
			}
			else
				i++;
		}
	}
	game->map[j] = NULL;
	close(fd);
}

char *read_fd(char *file,t_cub *game)
{
	int fd;
	char *line;
	char *aux;

	aux = NULL;
	fd = open(file,O_RDONLY);
	if (fd < 0)
		error_msg("Error: Open File\n",NULL);
	line = ft_strdup("");
	while(line)
	{
		free(line);
		line = get_next_line(fd);
		if (line)
		{
			ft_check_line(line,game);
			aux = ft_joinfree(aux,line);
		}
		if (game->count_data == 6)
			game->count_map++;
		else
			game->count_line++;
	}
	close(fd);
	return(aux);
}
