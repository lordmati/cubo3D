#include "../Include/cub3D.h"

void load_textures(t_cub *game)
{
	game->texture_wall_n = mlx_load_png(game->north);
	if (!game->texture_wall_n)
    	error_msg("Failed to load north texture", game);
	game->texture_wall_s= mlx_load_png(game->south);
	if (!game->texture_wall_s)
    	error_msg("Failed to load south texture", game);
	game->texture_wall_e = mlx_load_png(game->east);
	if (!game->texture_wall_e)
    	error_msg("Failed to load east texture", game);
	game->texture_wall_w = mlx_load_png(game->west);
	if (!game->texture_wall_w)
    	error_msg("Failed to load west texture", game);
}

void paint_texture(t_ray *ray, t_cub *game)
{
    if (ray->side == 0)
    {
        ray->wallX = game->y + ray->distance * ray->sin;
        if (ray->stepX == -1)
            game->current_texture = game->texture_wall_n;
        else
            game->current_texture = game->texture_wall_s;
    }
    else
    {
        ray->wallX = game->x + ray->distance * ray->cos;
        if (ray->stepY == -1)
            game->current_texture = game->texture_wall_w;
        else
            game->current_texture = game->texture_wall_e;
    }

    ray->wallX -= floor(ray->wallX);
    if (ray->wallX < 0)
        ray->wallX += 1.0;
    ray->texX = (int)(ray->wallX * game->current_texture->width);
    if (ray->texX >= (int)game->current_texture->width)
        ray->texX = (int)game->current_texture->width - 1;
    if (ray->texX < 0)
        ray->texX = 0;
}
