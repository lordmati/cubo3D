#include "../Include/cub3D.h"

static long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
void	init_torch(t_cub *game)
{
	int i;
	char *aux;
	char *tmp;
	char *extension;

	i = -1;
	game->torch = malloc(sizeof(t_torch));
	if (!game->torch)
		error_msg("Error malloc allocated",game);
	game->torch->last_time = get_time();
	game->torch->current_frame = 0;
	extension = ft_strdup(".png");
	while(++i < 80)
	{
		tmp = ft_itoa(i + 1);
		aux = ft_strjoin("Torch/torchmc",tmp);
		free(tmp);
		tmp = ft_strjoin(aux, extension);
		free(aux);
		game->torch->frames[i] = mlx_load_png(tmp);
		if(!game->torch->frames[i])
			error_msg("Error load torch\n",game);
		free(tmp);
	}
	free(extension);
}

void loop_animation(void *param)
{
	t_cub *game;

	game = (t_cub *)param;
	if (get_time() - game->torch->last_time >= ANIMATION)
	{
		game->torch->last_time = get_time();
		game->torch->current_frame = (game->torch->current_frame + 1) % TORCH;
		mlx_delete_image(game->mlx,game->torch->image);
		game->torch->image = mlx_texture_to_image(game->mlx,game->torch->frames[game->torch->current_frame]);
		if (!game->torch->image)
			error_msg("Error: load texture torch\n",game);
		mlx_image_to_window(game->mlx,game->torch->image,MAP_WIDTH * 0.7, MAP_HEIGHT - (500 * 0.9));
	}
}
