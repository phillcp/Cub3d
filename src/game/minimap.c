/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 06:21:59 by fiheaton          #+#    #+#             */
/*   Updated: 2026/03/12 21:01:57 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

u_int32_t	create_trgb(u_int32_t t, u_int32_t r, u_int32_t g, u_int32_t b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

static u_int32_t	pick_color(char map_tile)
{
	u_int32_t	color;

	if (map_tile == 'W')
		color = create_trgb(255, 0, 0, 0);
	else if (map_tile == 'D')
		color = create_trgb(255, 255, 0, 255);
	else if (map_tile == 'T')
		color = create_trgb(255, 255, 255, 0);
	else
		color = create_trgb(255, 255, 255, 255);
	return (color);
}

void	draw_circle(t_img *img, int xo, int yo, u_int32_t	color)
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

static void	draw_player(int x, int y, t_game *g)
{
	draw_circle2(g->img, SCREEN_WIDTH - x * MINIMAP_TILE_SIZE +
		MINIMAP_TILE_SIZE / 2, y * MINIMAP_TILE_SIZE
		+ MINIMAP_TILE_SIZE / 2, create_trgb(255, 0, 255, 0));
}

static void	draw_square(int x, int y, int color, t_game *g)
{
	int	k;
	int	l;

	k = -1;
	while (++k < MINIMAP_TILE_SIZE)
	{
		l = -1;
		while (++l < MINIMAP_TILE_SIZE)
		{
			if (SCREEN_WIDTH - x * MINIMAP_TILE_SIZE + k >= 0
				&& SCREEN_WIDTH - x * MINIMAP_TILE_SIZE + k < SCREEN_WIDTH
				&& y * MINIMAP_TILE_SIZE + l >= 0
				&& y * MINIMAP_TILE_SIZE + l < SCREEN_HEIGHT)
				pixel_put(g->img, SCREEN_WIDTH - x * MINIMAP_TILE_SIZE + k,
					y * MINIMAP_TILE_SIZE + l, color);
		}
	}
}

void	draw_minimap(t_game *game)
{
	int			j;
	int			i;
	u_int32_t	c;

	i = -1;
	while (++i < game->map.height)
	{
		j = 0;
		while (++j <= game->map.width)
		{
			c = pick_color(game->map.grid[i][game->map.width - j]);
			draw_square(j, i, c, game);
		}
	}
	draw_player((game->map.width - (int)game->player.pos.x),
		(int)game->player.pos.y, game);
}
