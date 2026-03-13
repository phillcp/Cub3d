/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 18:16:31 by gude-and          #+#    #+#             */
/*   Updated: 2026/03/13 00:30:13 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>
# include <sys/stat.h>

# include "libft.h"
# include "gnl.h"
# include "mlx.h"
# include "mlx_keys.h"

# define TEXTURE_SIZE	64
# define MINIMAP_TILE_SIZE 10
# define SCREEN_WIDTH 1024
# define SCREEN_HEIGHT 512
# define MAP_CHARS "01NSEW "
# define PLAYER_CHARS "NSEW"
# define RGB_MAX 255
# define MOVE_SPEED 0.08
# define ROT_SPEED 0.1
# define TILE_SIZE 1
# define FOV 1.5708
# define PI 3.141592653
# define CIRCLE_RADIUS 20

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

# define MLX_KEY_ESC 65307
# define MLX_KEY_W 119
# define MLX_KEY_A 97
# define MLX_KEY_S 115
# define MLX_KEY_D 100
# define MLX_KEY_LEFT 65361
# define MLX_KEY_RIGHT 65363

typedef struct s_pos
{
	double	x;
	double	y;
}	t_pos;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
}	t_img;

typedef struct s_ray
{
	double	rx;
	double	ry;
	double	z;
	t_pos	tex;
	int		**texture;
	double	lh;
	double	lo;
	double	texoff;
	t_pos	off;
}	t_ray;

typedef struct s_player
{
	t_pos	pos;
	t_pos	delta;
	double	dir_x;
	double	dir_y;
	float	orient;
}	t_player;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;

typedef struct s_texture
{
	char	*path;
	int		**tex;
}	t_texture;

typedef struct s_game
{
	void		*mlx;
	t_img		*img;
	void		*win;
	int			open_fd;
	t_player	player;
	t_map		map;
	t_texture	no_tex;
	t_texture	so_tex;
	t_texture	we_tex;
	t_texture	ea_tex;
	u_int32_t	floor_color;
	u_int32_t	ceiling_color;
}	t_game;

/* main.c */
int		main(int argc, char **argv);

/* parser/parse_file.c */
void	parse_cub_file(t_game *game, char *filename);

/* parser/parse_textures.c */
// int		parse_texture(t_texture *tex, char *line, const char *id);

/* parser/parse_colors.c */
// int		parse_color(int *color, char *line, const char *id);

/* parser/parse_map.c */
int		parse_map(t_game *game, int fd, char *first_line);
int		is_map_line(char *line);

/* parser/validate_map.c */
void	validate_map(t_game *game);

/* parser/init_player.c */
void	init_player_from_map(t_game *game, int px, int py);

/* utils/error.c */
void	exit_errorfd(t_game *game, char *message);
void	exit_error(t_game *game, char *message);

/* utils/free.c */
void	free_game(t_game *game);
void	free_matrix(int **matrix);
void	ft_free_split(char **split);
void	free_map_grid(char **grid, int height);

/* game/init_game.c */
void	init_game(t_game *game);

/* game/3d.c */
void	draw_3d(t_game *game);
void	pixel_put(t_img *img, int x, int y, u_int32_t color);

/* game/minimap.c */
void	draw_minimap(t_game *game);

/* game/movement.c */
void	move(t_game *game, int keycode);
void	rotate(t_game *game, int keycode);

/* game/ray_cast.c*/
t_ray	*check_wall(t_game *g, t_pos pos, double ang, float pa);

#endif
