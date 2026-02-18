/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 15:21:33 by fiheaton          #+#    #+#             */
/*   Updated: 2026/02/18 17:36:42 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_game_struct(t_game *game)
{
	ft_memset(game, 0, sizeof(t_game));
	game->floor_color = -1;
	game->ceiling_color = -1;
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		exit_error("Usage: ./cub3d <map.cub>");
		return (1);
	}
	init_game_struct(&game);
	if (!parse_cub_file(&game, argv[1]))
	{
		free_game(&game);
		return (1);
	}
	init_game(&game);
	free_game(&game);
	return (0);
}
