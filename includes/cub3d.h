/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 18:16:31 by gude-and          #+#    #+#             */
/*   Updated: 2026/02/20 06:16:19 by fiheaton         ###   ########.fr       */
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
# include "image.h"

# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 600
# define MAP_CHARS "01NSEW "
# define PLAYER_CHARS "NSEW"
# define RGB_MAX 255
# define MOVE_SPEED 0.08
# define ROT_SPEED 0.1
# define TILE_SIZE 1
# define FOV 60
# define PI 3.141592653

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

typedef struct s_player
{
	t_pos	pos;
	t_pos	delta;
	double	dir_x;
	double	dir_y;
	float	orient;
	double	plane_x;
	double	plane_y;
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
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}	t_texture;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_screen	screen;
	void		*img;
	char		*img_addr;
	int			img_bpp;
	int			img_line_len;
	int			img_endian;
	t_player	player;
	t_map		map;
	t_texture	no_tex;
	t_texture	so_tex;
	t_texture	we_tex;
	t_texture	ea_tex;
	int			floor_color;
	int			ceiling_color;
}	t_game;

/* main.c */
int		main(int argc, char **argv);

/* parser/parse_file.c */
int		parse_cub_file(t_game *game, char *filename);

/* parser/parse_textures.c */
int		parse_texture(t_texture *tex, char *line, const char *id);

/* parser/parse_colors.c */
int		parse_color(int *color, char *line, const char *id);

/* parser/parse_map.c */
int		parse_map(t_game *game, int fd, char *first_line);
int		is_map_line(char *line);

/* parser/validate_map.c */
int		validate_map(t_game *game);

/* parser/init_player.c */
int		init_player_from_map(t_game *game);

/* utils/error.c */
void	exit_error(char *message);

/* utils/free.c */
void	free_game(t_game *game);
void	ft_free_split(char **split);
void	free_map_grid(char **grid, int height);

/* game/init_game.c */
void	init_game(t_game *game);

/* game/3d.c */
void	draw3d(t_game *game);

/* game/movement.c */
void	move(t_game *game, int keycode);
void	rotate(t_game *game, int keycode);

/* game/mlx_raper.c */
void	my_mlx_put_image_to_window(t_game *game);

#endif
