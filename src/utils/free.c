/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 18:22:47 by gude-and          #+#    #+#             */
/*   Updated: 2026/03/12 21:03:38 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_map_grid(char **grid, int height)
{
	int	i;

	if (!grid)
		return ;
	i = 0;
	while (i < height)
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}

static void	free_matrix(void **matrix)
{
	int	i;

	if (!matrix)
		return ;
	i = -1;
	while (matrix[++i])
		free(matrix[i]);
	free(matrix);
}

static void	free_textures(t_game *game)
{
	if (game->no_tex.path)
		free(game->no_tex.path);
	if (game->no_tex.tex)
		free_matrix(game->no_tex.tex);
	if (game->so_tex.path)
		free(game->so_tex.path);
	if (game->so_tex.tex)
		free_matrix(game->so_tex.tex);
	if (game->we_tex.path)
		free(game->we_tex.path);
	if (game->we_tex.tex)
		free_matrix(game->we_tex.tex);
	if (game->ea_tex.path)
		free(game->ea_tex.path);
	if (game->ea_tex.tex)
		free_matrix(game->ea_tex.tex);
}

static void	free_screen(t_game *game)
{
	if (game->img && game->img->img)
		mlx_destroy_image(game->mlx, game->img->img);
	if (game->img)
		free(game->img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
}

void	free_game(t_game *game)
{
	if (game)
	{
		free_textures(game);
		free_map_grid(game->map.grid, game->map.height);
		free_screen(game);
		if (game->mlx)
			free(game->mlx);
	}
}

void	ft_free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
