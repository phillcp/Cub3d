/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: github-copilot                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 00:00:00 by github-copilot    #+#    #+#             */
/*   Updated: 2026/02/18 00:00:00 by github-copilot   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	map_at(t_map *map, int x, int y)
{
	int	row_len;

	if (y < 0 || y >= map->height)
		return (' ');
	if (!map->grid[y])
		return (' ');
	row_len = ft_strlen(map->grid[y]);
	if (x < 0 || x >= row_len)
		return (' ');
	return (map->grid[y][x]);
}

static void check_player_count(t_game *game)
{
	int		y;
	int		x;
	int		p_count;

	p_count = 0;
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (game->map.grid[y][x])
		{
			if (ft_strchr(PLAYER_CHARS, game->map.grid[y][x]))
			{
				if (p_count)
					exit_error(game, "Map must only have one player");
				p_count = 1;
				init_player_from_map(game, x, y);
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	check_surroundings(t_map map, int row, int column)
{
	if (map.grid[row][column - 1] == ' '
		|| map.grid[row][column + 1] == ' '
		|| map.grid[row - 1][column] == ' '
		|| map.grid[row + 1][column] == ' ')
		return (0);
	else
		return (1);
}

int	check_enclosed(t_map map)
{
	int		row;
	int		column;
	int		row_start;
	int		col_start;

	row = -1;
	row_start = 0;
	col_start = 0;
	while (++row < map.height)
	{
		column = -1;
		while (map.grid[row][++column] != '\0')
		{
			if (map.grid[row][column] == '0')
			{
				if (row == 0 || row == map.height -1
					|| column == 0 || column == map.width - 1)
					return (0);
				if (!check_surroundings(map, row, column))
					return (0);
			}
		}
	}
	return (1);
}

void	validate_map(t_game *game)
{
	if (!game || !game->map.grid)
		exit_error(game, "Map is missing");
	check_player_count(game);
	if (!check_enclosed(game->map))
		exit_error(game, "Map is not enclosed");
	return (1);
}
