/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 18:01:02 by fiheaton          #+#    #+#             */
/*   Updated: 2026/02/18 17:49:14 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_3d_bg(t_game *game, int floor_color, int ceiling_color)
{
	(void)game;
	(void)floor_color;
	(void)ceiling_color;
}

static void	draw_walls(t_game *game, t_pos player_pos)
{
	(void)game;
	(void)player_pos;
}

static void	draw2d(t_game *game)
{
	(void)game;
}

void	draw3d(t_game *game)
{
	draw_3d_bg(game, game->floor_color, game->ceiling_color);
	draw_walls(game, game->player.pos);
	draw2d(game);
	my_mlx_put_image_to_window(game);
}
