/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:39:36 by gude-and          #+#    #+#             */
/*   Updated: 2026/02/18 17:39:49 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static float	get_orient(char c)
{
	if (c == 'N')
		return (M_PI / 2);
	if (c == 'S')
		return (3 * M_PI / 2);
	if (c == 'E')
		return (0);
	if (c == 'W')
		return (M_PI);
	return (0);
}

static void	set_player_direction(t_player *player)
{
	player->dir_x = cos(player->orient);
	player->dir_y = -sin(player->orient);
	player->plane_x = -player->dir_y * 0.66;
	player->plane_y = player->dir_x * 0.66;
	player->delta.x = cos(player->orient) * MOVE_SPEED;
	player->delta.y = -sin(player->orient) * MOVE_SPEED;
}

static void	find_player_pos(t_game *game, int *px, int *py)
{
	int	y;
	int	x;

	*px = -1;
	*py = -1;
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (game->map.grid[y][x])
		{
			if (ft_strchr(PLAYER_CHARS, game->map.grid[y][x]))
			{
				*px = x;
				*py = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

int	init_player_from_map(t_game *game)
{
	int		px;
	int		py;
	char	spawn;

	find_player_pos(game, &px, &py);
	if (px == -1 || py == -1)
		return (exit_error("Player position not found"), 0);
	spawn = game->map.grid[py][px];
	game->map.grid[py][px] = '0';
	game->player.pos.x = (double)px + 0.5;
	game->player.pos.y = (double)py + 0.5;
	game->player.orient = get_orient(spawn);
	set_player_direction(&game->player);
	return (1);
}
