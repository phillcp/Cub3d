/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 16:46:38 by fiheaton          #+#    #+#             */
/*   Updated: 2026/02/10 19:15:57 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	stop(void *param)
{
	t_game	*game;
	int		status_code;

	game = (t_game *)param;
	free_game(game);
	exit(status_code);
}

int key_handler(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *)game;
	if (keycode == MLX_KEY_ESC)
		stop(game);
	else if (keycode == MLX_KEY_W || keycode == MLX_KEY_S \
		|| keycode == MLX_KEY_A || keycode == MLX_KEY_D)
		move(game, keycode);
	else if (keycode == MLX_KEY_LEFT || keycode == MLX_KEY_RIGHT)
		rotate(game, keycode);
	return (1);
}

void	init_game(t_game *game)
{
	mlx_hook(game->win, 17, (1L << 17), free_game, game);
	mlx_key_hook(game->win, key_handler, game);
	mlx_loop_hook(game->mlx, draw3d, game);
}
