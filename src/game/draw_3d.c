/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 17:57:18 by gude-and          #+#    #+#             */
/*   Updated: 2026/03/15 17:57:44 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_3d(t_game *game)
{
	float		pa;

	pa = fix_angle(game->player.orient);
	draw_bg(game, game->floor_color, game->ceiling_color);
	draw_walls(game, game->player.pos, pa);
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img->img, 0, 0);
}
