/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 18:19:31 by gude-and          #+#    #+#             */
/*   Updated: 2026/03/12 22:14:31 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	fill_matrix(t_img *tmp, int **texture, int height, int width)
{
	int				x;
	int				y;
	unsigned char	*c;

	y = -1;
	while (++y < height)
	{
		x = -1;
		while (++x < width)
		{
			c = (unsigned char *)tmp->addr + (y * tmp->line_len + (x * \
				(tmp->bpp / 8)));
			texture[y][x] = (unsigned int)(c[3] << 24 | c[2] << 16 \
				| c[1] << 8 | c[0]);
		}
	}
}

static int	**new_matrix(t_game *game)
{
	int		**tex;
	int		y;

	tex = ft_calloc(TEXTURE_SIZE + 1, sizeof(int *));
	if (!tex)
		exit_error(game, "Failed allocation while getting new_tex arr");
	y = -1;
	while (++y < TEXTURE_SIZE)
	{
		tex[y] = ft_calloc(TEXTURE_SIZE, sizeof(int));
		if (!tex[y])
		{
			free_matrix(tex);
			exit_error(game, "Failed allocation while getting new_tex line");
		}
	}
	return (tex);
}

int	**load_tex(t_game *game, char *path)
{
	int		**tex;
	t_img	*tmp;
	int		h;
	int		w;

	if (!path)
		exit_error(game, "Missing path to texture");
	tmp = ft_calloc(1, sizeof(t_img));
	if (!tmp)
		exit_error(game, "Failed allocation while loading texture");
	tmp->img = mlx_xpm_file_to_image(game->mlx, path, &w, &h);
	if (!tmp->img)
	{
		free(tmp);
		exit_error(game, "Failed to load texture image");
	}
	tmp->addr = mlx_get_data_addr(tmp->img, &tmp->bpp, &tmp->line_len, \
		&tmp->endian);
	if (!tmp->addr)
		exit_error(game, "Failed to get data addr while importing texture");
	tex = new_matrix(game);
	fill_matrix(tmp, tex, h, w);
	mlx_destroy_image(game->mlx, tmp->img);
	free(tmp);
	return (tex);
}

void	load_textures(t_game *game)
{
	game->no_tex.tex = load_tex(game, game->no_tex.path);
	game->so_tex.tex = load_tex(game, game->so_tex.path);
	game->we_tex.tex = load_tex(game, game->we_tex.path);
	game->ea_tex.tex = load_tex(game, game->ea_tex.path);
}
