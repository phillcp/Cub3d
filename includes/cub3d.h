/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 18:16:31 by gude-and          #+#    #+#             */
/*   Updated: 2026/02/10 18:37:21 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// Includes de bibliotecas padrão
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>

// Includes da libft (assumimos que get_next_line está lá)
# include "libft.h"
# include "gnl.h"
# include "mlx_keys.h"

// Constantes úteis
# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 600
# define MAP_CHAR "01NSEW "
# define RGB_MAX 255

// Códigos de teclado (exemplos, podem variar)
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

# define M_PI	3.141592653
# define MOVE_SPEED	0.08
# define TILE_SIZE 1

// Estrutura para informações do jogador

// norminette
typedef struct s_pos
{
	double		x;
	double		y;
}	t_pos;

typedef struct s_player
{
	t_pos	pos;
	t_pos	delta;
    double  pos_x;      // Posição X no mapa
    double  pos_y;      // Posição Y no mapa
    double  dir_x;      // Vetor direção X
    double  dir_y;      // Vetor direção Y
	float	orient;		// Orientaçao do player
    double  plane_x;    // Plano da câmera X
    double  plane_y;    // Plano da câmera Y
    double  move_speed; // Velocidade de movimento
    double  rot_speed;  // Velocidade de rotação
}   t_player;

// Estrutura para informações do mapa
typedef struct s_map
{
    char    **grid;     // Grid 2D do mapa
    int     width;      // Largura do mapa
    int     height;     // Altura do mapa
}   t_map;

// Estrutura para informações de textura (por enquanto, só o caminho)
typedef struct s_texture
{
    char    *path;      // Caminho do arquivo .xpm
    void    *img;       // Ponteiro para imagem MLX (para o futuro)
    char    *addr;      // Endereço dos dados (para o futuro)
    int     width;
    int     height;
    int     bpp;        // Bits per pixel
    int     line_len;
    int     endian;
}   t_texture;

// Estrutura principal que contém todos os dados do jogo
typedef struct s_game
{
    void        *mlx;           // Ponteiro MLX (para o futuro)
    void        *win;           // Ponteiro janela (para o futuro)
    t_player    player;         // Dados do jogador
    t_map       map;            // Dados do mapa
    t_texture   no_tex;         // Textura Norte
    t_texture   so_tex;         // Textura Sul
    t_texture   we_tex;         // Textura Oeste
    t_texture   ea_tex;         // Textura Leste
    int         floor_color;    // Cor do chão (RGB)
    int         ceiling_color;  // Cor do teto (RGB)
}   t_game;

// --- Protótipos de Funções ---

// main.c
int             main(int argc, char **argv);

// parser/parse_file.c
int             parse_cub_file(t_game *game, char *filename);

// parser/parse_textures.c
int             parse_texture(t_texture *texture, char *line, const char *identifier);

// parser/parse_colors.c
int             parse_color(int *color, char *line, const char *identifier);

// utils/error.c
void            exit_error(char *message);

// utils/free.c
void            free_game(t_game *game);
void            ft_free_split(char **split);

// game/init_game.c
void			init_game(t_game *game);

// game/3d.c
void			draw3d(t_game *game);

#endif
