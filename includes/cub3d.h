/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 18:16:31 by gude-and          #+#    #+#             */
/*   Updated: 2026/03/18 19:57:17 by gude-and         ###   ########.fr       */
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
	char		*map_filename;
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
void	parse_line(t_game *game, char *line);
int		all_elements_parsed(t_game *game);

/* parser/parse_elements.c */
void	parse_texture_path(t_game *game, char *line);
void	parse_color(t_game *game, char *line);

/* parser/parse_textures.c */
void	load_textures(t_game *game);
int		**load_tex(t_game *game, char *path);

/* parser/parser_map.c */
int		parse_map(t_game *game, char *first_line, int map_start_line);

/* parser/parser_map_validation.c */
void	validate_map_line(t_game *game, char *line, int *found_empty);

/* parser/parser_map_utils.c */
int		is_map_line(char *line);
int		line_len_without_nl(char *line);
void	update_map_width(t_map *map, char *line);
char	*build_padded_map_line(t_game *game, char *line);

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
void	draw_bg(t_game *game, int f_color, int c_color);
void	draw_walls(t_game *game, t_pos pos, float pa);
float	fix_angle(float pa);

/* game/minimap.c */
void	draw_minimap(t_game *game);
void	draw_player(int x, int y, t_game *g);
void	draw_mini_bg(int x, int y, int color, t_game *g);
void	draw_circle(t_img *img, int xo, int yo, u_int32_t color);

/* game/movement.c */
void	move(t_game *game, int keycode);
void	rotate(t_game *game, int keycode);

/* game/ray_cast.c*/
t_ray	*check_wall(t_game *g, t_pos pos, double ang, float pa);

#endif
