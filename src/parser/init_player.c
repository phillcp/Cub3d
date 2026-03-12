/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:39:36 by gude-and          #+#    #+#             */
/*   Updated: 2026/03/12 20:01:16 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static float	get_orient(char c)
{
	if (c == 'N')
		return (PI / 2);
	else if (c == 'S')
		return (3 * PI / 2);
	else if (c == 'E')
		return (0);
	else if (c == 'W')
		return (PI);
	return (0);
}

static void	set_player_direction(t_player *player)
{
	player->dir_x = cos(player->orient);
	player->dir_y = -sin(player->orient);
	player->delta.x = cos(player->orient) * MOVE_SPEED;
	player->delta.y = -sin(player->orient) * MOVE_SPEED;
}

void	init_player_from_map(t_game *game, int px, int py)
{
	char	spawn;

	spawn = game->map.grid[py][px];
	game->map.grid[py][px] = '0';
	game->player.pos.x = (double)(px * TILE_SIZE) + 0.5;
	game->player.pos.y = (double)(px * TILE_SIZE) + 0.5;
	game->player.orient = get_orient(spawn);
	set_player_direction(&game->player);
}
