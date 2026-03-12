/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 17:14:41 by fiheaton          #+#    #+#             */
/*   Updated: 2026/03/12 21:25:49 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	can_move(t_game *game, t_pos dest)
{
	t_pos	tile;
	char	dest_tile;

	tile.x = dest.x / TILE_SIZE;
	tile.y = dest.y / TILE_SIZE;
	dest_tile = game->map.grid[(int)tile.y][(int)tile.x];
	if (dest_tile != '1')
	{
		game->player.pos.x = dest.x;
		game->player.pos.y = dest.y;
	}
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
	t_pos		delta;

	player = game->player;
	dest.x = player.pos.x;
	dest.y = player.pos.y;
	if (keycode == MLX_KEY_W)
	{
		dest.x = player.pos.x + player.dir_x;
		dest.y = player.pos.y + player.dir_y;
	}
	else if (keycode == MLX_KEY_S)
	{
		dest.x = player.pos.x - player.dir_x;
		dest.y = player.pos.y - player.dir_y;
	}
	else if (keycode == MLX_KEY_A || keycode == MLX_KEY_D)
	{
		delta = get_sideways_dest(player, keycode);
		dest.x = player.pos.x + delta.x;
		dest.y = player.pos.y + delta.y;
	}
	can_move(game, dest);
}

void	rotate(t_game *game, int keycode)
{
	if (keycode == MLX_KEY_LEFT)
	{
		game->player.orient += ROT_SPEED;
		if (game->player.orient > 2 * PI)
			game->player.orient -= 2 * PI;
	}
	else if (keycode == MLX_KEY_RIGHT)
	{
		game->player.orient -= ROT_SPEED;
		if (game->player.orient < 0)
			game->player.orient += 2 * PI;
	}
	game->player.delta.x = cos(game->player.orient) * MOVE_SPEED;
	game->player.delta.y = -sin(game->player.orient) * MOVE_SPEED;
}
