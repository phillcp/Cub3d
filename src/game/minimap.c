/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 06:21:59 by fiheaton          #+#    #+#             */
/*   Updated: 2026/03/18 19:48:39 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

u_int32_t	create_trgb(u_int32_t t, u_int32_t r, u_int32_t g, u_int32_t b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

u_int32_t	pick_color(char map_tile)
{
	u_int32_t	color;

	if (map_tile == '1')
		color = create_trgb(255, 0, 0, 0);
	else if (map_tile == '0')
		color = create_trgb(255, 255, 255, 255);
	else
		color = create_trgb(0, 0, 0, 0);
	return (color);
}

void	draw_circle(t_img *img, int xo, int yo, u_int32_t color)
{
	int	radius;
	int	x;
	int	y;

	radius = CIRCLE_RADIUS;
	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (pow(x, 2) + pow(y, 2) - radius < 0)
				pixel_put(img, x + xo, y + yo, color);
			x++;
		}
		y++;
	}
}

void	draw_player(int x, int y, t_game *g)
{
	draw_circle(g->img,
		x * MINIMAP_TILE_SIZE + MINIMAP_TILE_SIZE / 2,
		y * MINIMAP_TILE_SIZE + MINIMAP_TILE_SIZE / 2,
		create_trgb(255, 0, 255, 0));
}

void	draw_mini_bg(int x, int y, int color, t_game *g)
{
	int	k;
	int	l;

	k = -1;
	while (++k < MINIMAP_TILE_SIZE)
	{
		l = -1;
		while (++l < MINIMAP_TILE_SIZE)
		{
			if (x * MINIMAP_TILE_SIZE + k >= 0
				&& x * MINIMAP_TILE_SIZE + k < SCREEN_WIDTH
				&& y * MINIMAP_TILE_SIZE + l >= 0
				&& y * MINIMAP_TILE_SIZE + l < SCREEN_HEIGHT)
				pixel_put(g->img, x * MINIMAP_TILE_SIZE + k,
					y * MINIMAP_TILE_SIZE + l, color);
		}
	}
}
