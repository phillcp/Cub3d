/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 17:14:41 by fiheaton          #+#    #+#             */
/*   Updated: 2026/03/13 00:46:05 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	can_move(t_game *game, t_pos dest)
{
	int		tile_x;
	int		tile_y;
	char	dest_tile;

	tile_x = dest.x / TILE_SIZE;
	tile_y = dest.y / TILE_SIZE;
	dest_tile = game->map.grid[tile_y][tile_x];
	if (dest_tile != '1')
		game->player.pos = dest;
}

static t_pos	get_sideways_dest(t_player player, int keycode)
{
	float	orient;
	t_pos	delta;

	orient = player.orient;
	if (keycode == MLX_KEY_A)
	{
		orient += PI / 2;
		if (orient > 2 * PI)
			orient -= 2 * PI;
	}
	else if (keycode == MLX_KEY_D)
	{
		orient -= PI / 2;
		if (orient < 0)
			orient += 2 * PI;
	}
	delta.x = cos(orient) * MOVE_SPEED;
	delta.y = -sin(orient) * MOVE_SPEED;
	return (delta);
}

void	move(t_game *game, int keycode)
{
	t_player	player;
	t_pos		dest;

	player = game->player;
	dest = player.pos;
	if (keycode == MLX_KEY_W)
	{
		dest.x = player.pos.x + player.delta.x;
		dest.y = player.pos.y + player.delta.y;
	}
	else if (keycode == MLX_KEY_S)
	{
		dest.x = player.pos.x - player.delta.x;
		dest.y = player.pos.y - player.delta.y;
	}
	else if (keycode == MLX_KEY_A || keycode == MLX_KEY_D)
	{
		dest = get_sideways_dest(player, keycode);
		dest.x = player.pos.x + dest.x;
		dest.y = player.pos.y + dest.y;
	}
	can_move(game, dest);
}

void	rotate(t_game *game, int keycode)
{
	float	*orient;
	t_pos	*delta;

	orient = &game->player.orient;
	delta = &game->player.delta;
	if (keycode == MLX_KEY_LEFT)
	{
		*orient += ROT_SPEED;
		if (*orient > 2 * PI)
			*orient -= 2 * PI;
	}
	else if (keycode == MLX_KEY_RIGHT)
	{
		*orient -= ROT_SPEED;
		if (*orient < 0)
			*orient += 2 * PI;
	}
	delta->x = cos(*orient) * MOVE_SPEED;
	delta->y = -sin(*orient) * MOVE_SPEED;
}
