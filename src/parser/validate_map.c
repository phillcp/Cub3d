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

static int	check_allowed_and_count_players(t_game *game, int *player_count)
{
	int		y;
	int		x;
	char	c;

	*player_count = 0;
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (game->map.grid[y][x])
		{
			c = game->map.grid[y][x];
			if (!ft_strchr(MAP_CHARS, c) && !ft_strchr(PLAYER_CHARS, c))
				return (exit_error("Invalid character in map"), 0);
			if (ft_strchr(PLAYER_CHARS, c))
				(*player_count)++;
			x++;
		}
		y++;
	}
	return (1);
}

static int	check_enclosed(t_game *game)
{
	int		w;
	int		h;
	int		size;
	int		*queue_x;
	int		*queue_y;
	int		front;
	int		rear;
	char	*visited;
	int		x;
	int		y;
	char	c;

	w = game->map.width;
	h = game->map.height;
	size = w * h;
	queue_x = malloc(sizeof(int) * size);
	queue_y = malloc(sizeof(int) * size);
	visited = ft_calloc(size, sizeof(char));
	if (!queue_x || !queue_y || !visited)
		return (exit_error("Memory allocation failed"), 0);
	front = 0;
	rear = 0;
	/* enqueue boundary cells that are not walls */
	y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			if (y == 0 || y == h - 1 || x == 0 || x == w - 1)
			{
				c = map_at(&game->map, x, y);
				if (c != '1')
				{
					queue_x[rear] = x;
					queue_y[rear] = y;
					rear++;
					visited[y * w + x] = 1;
				}
			}
			x++;
		}
		y++;
	}
	while (front < rear)
	{
		x = queue_x[front];
		y = queue_y[front];
		front++;
		c = map_at(&game->map, x, y);
		if (c == '0' || ft_strchr(PLAYER_CHARS, c))
		{
			free(queue_x);
			free(queue_y);
			free(visited);
			return (exit_error("Map is not closed"), 0);
		}
		if (x > 0 && !visited[y * w + (x - 1)] && map_at(&game->map, x - 1, y) != '1')
		{
			queue_x[rear] = x - 1;
			queue_y[rear] = y;
			rear++;
			visited[y * w + (x - 1)] = 1;
		}
		if (x + 1 < w && !visited[y * w + (x + 1)] && map_at(&game->map, x + 1, y) != '1')
		{
			queue_x[rear] = x + 1;
			queue_y[rear] = y;
			rear++;
			visited[y * w + (x + 1)] = 1;
		}
		if (y > 0 && !visited[(y - 1) * w + x] && map_at(&game->map, x, y - 1) != '1')
		{
			queue_x[rear] = x;
			queue_y[rear] = y - 1;
			rear++;
			visited[(y - 1) * w + x] = 1;
		}
		if (y + 1 < h && !visited[(y + 1) * w + x] && map_at(&game->map, x, y + 1) != '1')
		{
			queue_x[rear] = x;
			queue_y[rear] = y + 1;
			rear++;
			visited[(y + 1) * w + x] = 1;
		}
	}
	free(queue_x);
	free(queue_y);
	free(visited);
	return (1);
}

int	validate_map(t_game *game)
{
	int	player_count;

	if (!game || !game->map.grid)
		return (exit_error("Map is missing"), 0);
	if (!check_allowed_and_count_players(game, &player_count))
		return (0);
	if (player_count != 1)
		return (exit_error("Map must have exactly one player"), 0);
	if (!check_enclosed(game))
		return (0);
	return (1);
}
