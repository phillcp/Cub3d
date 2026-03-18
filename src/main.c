/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 15:21:33 by fiheaton          #+#    #+#             */
/*   Updated: 2026/03/18 19:47:59 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_game_struct(t_game *game)
{
	ft_memset(game, 0, sizeof(t_game));
	game->no_tex.path = NULL;
	game->so_tex.path = NULL;
	game->ea_tex.path = NULL;
	game->we_tex.path = NULL;
	game->no_tex.tex = NULL;
	game->so_tex.tex = NULL;
	game->ea_tex.tex = NULL;
	game->we_tex.tex = NULL;
	game->map.grid = NULL;
	game->map_filename = NULL;
	game->open_fd = -1;
	game->floor_color = -1;
	game->ceiling_color = -1;
	game->mlx = mlx_init();
	if (!game->mlx)
		exit_error(game, "Failed to init mlx");
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		exit_error(NULL, "Usage: ./cub3d <map.cub>");
		return (1);
	}
	init_game_struct(&game);
	parse_cub_file(&game, argv[1]);
	init_game(&game);
	free_game(&game);
	return (0);
}
