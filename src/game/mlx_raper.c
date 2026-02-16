/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_raper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 18:10:05 by fiheaton          #+#    #+#             */
/*   Updated: 2026/02/10 21:36:29 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_put_image_to_window(t_game *game)
{
	mlx_put_image_to_window(game->mlx, game->screen.win, game->screen.img, 0, 0);
}
