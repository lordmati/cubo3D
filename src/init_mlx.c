#include "../Include/cub3D.h"

static void wall_finder(t_ray *ray, t_cub *game)
{
	while(1)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->mapX += ray->stepX;
			ray->side = 0;
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->mapY += ray->stepY;
			ray->side = 1;
		}
		if (game->map[ray->mapY][ray->mapX] == '1'
			|| game->map[ray->mapY][ray->mapX] == '\n'
			|| game->map[ray->mapY][ray->mapX] == '\0'
			|| game->map[ray->mapY][ray->mapX] == ' ')
			break;
	}
}

static void ray_steps(t_ray *ray, t_cub *game)
{
	if (ray->cos < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (game->x - ray->mapX) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (ray->mapX + 1.0 -game->x) * ray->deltaDistX;
	}
	if (ray->sin < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (game->y - ray->mapY) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (ray->mapY + 1.0 - game->y) * ray->deltaDistY;
	}
}

static void dda_algorithm(t_ray *ray, t_cub *game, int i)
{
	int start, start2;
	int end, end2;
	double distance_corrected;
	ray->mapX = (int)game->x;
	ray->mapY = (int)game->y;
	ray->deltaDistX = fabs(1 / ray->cos);
	ray->deltaDistY = fabs(1 / ray->sin);
	ray_steps(ray, game);
	wall_finder(ray, game);
	if (ray->side == 0)
		ray->distance = (ray->mapX - game->x + (1 - ray->stepX)  / 2) / ray->cos;
	else
		 ray->distance = (ray->mapY - game->y + (1 - ray->stepY) / 2) / ray->sin;
	distance_corrected = ray->distance * cos (ray->ang - game->radian_view);
	start = MAP_HEIGHT/2 - (MAP_WIDTH/(2 * distance_corrected));
	end = MAP_HEIGHT/2 + (MAP_WIDTH/(2 * distance_corrected));
	if (start < 0)
		start2 = 0;
	else
		start2 = start;
	if(end >= MAP_HEIGHT)
		end2 = MAP_HEIGHT;
	else
		end2 = end;
	paint_texture(ray, game);
	for (int y = (int)start2; y < (int)end2; y++)
	{
		ray->texY = (int)((y - start) * (game->current_texture->height) / (end - start));
		if (ray->texY < 0)
			ray->texY = 0;
		if (ray->texY >= (int)game->current_texture->height)
			ray->texY = (int)game->current_texture->height - 1;
		uint32_t color = *(uint32_t *)(game->current_texture->pixels + 
                    (ray->texY * game->current_texture->width + ray->texX) * 4);
		color = (color & 0xff000000) >> 24 | (color & 0x00ff0000) >> 8 | (color & 0x0000ff00) << 8 | (color & 0x000000ff) << 24;
		mlx_put_pixel(game->cub_img, i, y, color);
	}
}


void ray_casting(t_ray *ray,t_cub *game)
{
	int i = 0;
	double ang;
	double start;
	double radian_fov;

	radian_fov = (FOV * M_PI) / 180;
	ang = (FOV / MAP_WIDTH) * M_PI / 180;
	start = game->radian_view - radian_fov / 2;
	while(i < MAP_WIDTH)
	{
		ray[i].ang = start + (ang * i);
		ray[i].sin = sin(ray[i].ang);
		ray[i].cos = cos(ray[i].ang);
		dda_algorithm(&ray[i], game, i);
		i++;
	}
}
void paint_all(t_cub *game,int x, int y)
{
	int rgb_ceiling;
	int rgb_floor;

	rgb_ceiling = rgb(game->arr_ceiling[0],game->arr_ceiling[1],game->arr_ceiling[2],255);
	rgb_floor = rgb(game->arr_floor[0],game->arr_floor[1],game->arr_floor[2],255);
	while(MAP_HEIGHT / 2 > y)
	{
		x = 0;
		while(MAP_WIDTH > x++)
			mlx_put_pixel(game->cub_img, x, y, rgb_ceiling);
		y++;
	}
	while(MAP_HEIGHT > y)
	{
		x = 0;
		while(MAP_WIDTH > x++)
			mlx_put_pixel(game->cub_img, x, y, rgb_floor);
		y++;
	}
}

void init_mlx(t_cub *game)
{
	t_ray ray[MAP_WIDTH];
	game->ray = ray;
	game->mlx = mlx_init(MAP_WIDTH,
			MAP_HEIGHT, "cub3D", false);
	game->cub_img = mlx_new_image(game->mlx, MAP_WIDTH, MAP_HEIGHT);
	init_torch(game);
	load_textures(game);
	paint_all(game,0,0);
	mlx_image_to_window(game->mlx, game->cub_img, 0, 0);
	ray_casting(game->ray,game);
	mlx_key_hook(game->mlx, &key_press, game);
	mlx_loop_hook(game->mlx,&mouse_move,game);
	mlx_loop_hook(game->mlx,&loop_animation,game);
	mlx_loop(game->mlx);
}
