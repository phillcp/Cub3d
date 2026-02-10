/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 18:01:02 by fiheaton          #+#    #+#             */
/*   Updated: 2026/02/10 19:15:56 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw3d(t_game *game)
{
	draw_3d_bg(game, game->floor_color, game->ceiling_color);
	draw_walls(game, game->player.pos);
	draw2d(game);
	raper_mlx_put_image_to_window(game);
}
