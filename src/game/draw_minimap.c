/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 17:56:15 by gude-and          #+#    #+#             */
/*   Updated: 2026/03/18 19:57:17 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

u_int32_t	pick_color(char map_tile);

void	draw_minimap(t_game *game)
{
	int			j;
	int			i;
	u_int32_t	c;

	i = -1;
	while (++i < game->map.height)
	{
		j = -1;
		while (++j < game->map.width)
		{
			c = pick_color(game->map.grid[i][j]);
			draw_mini_bg(j, i, c, game);
		}
	}
	draw_player(((int)game->player.pos.x),
		(int)game->player.pos.y, game);
}
