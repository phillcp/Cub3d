/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 18:01:02 by fiheaton          #+#    #+#             */
/*   Updated: 2026/02/10 22:28:43 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	pixel_put(t_img *img, int x, int y, u_int32_t color)
{
	char	*dst;

	if (!img)
		err_exit("NULL img @my_mlx_pixel_put", NULL);
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(u_int32_t *)dst = color;
}

void	pixel_put_tex(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	dst[3] = color >> 24;
	dst[2] = color >> 16;
	dst[1] = color >> 8;
	dst[0] = color;
}

static void	draw_bg(t_game *game, int f_color, int c_color)
{
	int	x;
	int	y;

	y = 0;
	while (y < (game->screen.height / 2))
	{
		x = -1;
		while (++x < game->screen.width)
			pixel_put(game->screen.img, x, y, c_color);
		++y;
	}
	while (y < game->screen.height)
	{
		while (++x < game->screen.width)
			pixel_put(game->screen.img, x, y, f_color);
		++y;
	}
}

static void	draw_walls(t_game *game, t_pos pos)
{
	t_ray	*check;
	double	angle;
	int		i;
	int		j;
	int		k;

	i = -1;
	while (++i < SCREEN_WIDTH)
	{
		angle = (i * FOV / SCREEN_WIDTH) - FOV / 2;
		angle = fmod(angle + (2 * M_PI), 2 * M_PI);
		check = check_wall(game, pos, angle);
		j = -1;
		while (++j < SCREEN_HEIGHT)
		{
			k = -1;
			while (++k < 1)
			{

			}
		}
	}
}

void	draw3d(t_game *game)
{
	draw_bg(game, game->floor_color, game->ceiling_color);
	draw_walls(game, game->player.pos);
	draw2d(game);
	raper_mlx_put_image_to_window(game);
}
