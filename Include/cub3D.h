#ifndef CUB3D_H
#define CUB3D_H

# include "LIBFT/includes/libft.h"
# include "MLX42_P2/include/MLX42/MLX42.h"
# include <math.h>
# include <sys/time.h>

# define MAP_WIDTH	1920
# define MAP_HEIGHT	1080

# define FOV		45.0
# define D_ANGLE	1.5
# define ANGLE_MOVE 0.0349
# define P_MOVE		0.075
# define M_PI		3.14159265358979323846
# define M_PI_2		1.57079632679489661923
# define TORCH		80
# define ANIMATION	50

typedef struct s_torch
{
	mlx_texture_t *frames[TORCH];
	mlx_image_t		*image;
	int 			current_frame;
	int				last_time;
} t_torch;

typedef struct s_ray
{
	double ang;
	double cos;
	double sin;
	double distance;
	double sideDistX;
	double sideDistY;
	double deltaDistX;
	double deltaDistY;
	double wallX;
	int side;
	int stepX;
	int stepY;
	int mapX;
	int mapY;
	int texX;
	int texY;
}	t_ray;

typedef struct s_cub
{
	int		count_map;
	int		count_data;
	int		count_line;
	int		*arr_ceiling;
	int		*arr_floor;
	int		value_rgb_floor;
	int		value_rgb_ceiling;
	int 	player;
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	char	*floor;
	char	*ceiling;
	char	**map;
	char	*info;
	double	y;
	double	x;
	char	player_view;
	double	radian_view;
	t_torch	*torch;
	t_ray	*ray;
	mlx_t			*mlx;
	mlx_image_t		*cub_img;
	mlx_texture_t	*texture_floor;
	mlx_texture_t	*texture_wall_n;
	mlx_texture_t	*texture_wall_s;
	mlx_texture_t	*texture_wall_e;
	mlx_texture_t	*texture_wall_w;
	mlx_texture_t	*texture_exit;
	mlx_texture_t	*texture_coin;
	mlx_texture_t	*texture_player;
	mlx_texture_t	*current_texture;
	mlx_image_t		*image_floor;
	mlx_image_t		*image_wall;
	mlx_image_t		*image_exit;
	mlx_image_t		*image_coin;
	mlx_image_t		*image_player;
}	t_cub;

//Checks
void check_extension(char *str);
void ft_check_line(char *line,t_cub *game);
void check_info(t_cub *game);

//check map
void check_map(char **map,t_cub *game);
void check_caracter_map(char **map,t_cub *game);
void check_valid_position_player(char **map,t_cub *game);

//save_fd
void save_map(t_cub *game,char *file,int i, int j);
char *read_fd(char *file,t_cub *game);
void save_player(char c,int y,int x,t_cub *game);

//valid_info
void valid_info(char *str,t_cub *game);
int *valid_numbers(char *str,t_cub *game);

//utils
char *ft_joinfree(char *s1, char *s2);
int	skip_spaces(char *str);
int count_comma(char *str);
void free_matrix(char **str);
int rgb(int r,int g,int b, int a);

//set_view
double set_view(t_cub *game);

//init mlx
void init_mlx(t_cub *game);
void paint_all(t_cub *game,int x, int y);
void ray_casting(t_ray *ray,t_cub *game);

//paint_texture
void load_textures(t_cub *game);
void paint_texture(t_ray *ray, t_cub*game);

//moves player
void	key_press(mlx_key_data_t key, void *data);
void	mouse_move(void *data);

//torch animation
void	loop_animation(void *param);
void	init_torch(t_cub *game);


//exit

void error_msg(char *str,t_cub *game);


#endif