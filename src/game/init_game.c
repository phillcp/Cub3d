/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 16:46:38 by fiheaton          #+#    #+#             */
/*   Updated: 2026/03/18 19:48:31 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	close_handler(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	free_game(game);
	exit(0);
	return (1);
}

int	loop_handler(void *param)
{
	draw_3d((t_game *)param);
	return (1);
}

int	key_handler(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keycode == MLX_KEY_ESC)
		close_handler(game);
	else if (keycode == MLX_KEY_W || keycode == MLX_KEY_S \
		|| keycode == MLX_KEY_A || keycode == MLX_KEY_D)
		move(game, keycode);
	else if (keycode == MLX_KEY_LEFT || keycode == MLX_KEY_RIGHT)
		rotate(game, keycode);
	return (0);
}

static void	init_screen(t_game *game)
{
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
	if (!game->win)
		exit_error(game, "Failed to create window");
	game->img = malloc(sizeof(t_img));
	if (!game->img)
		exit_error(game, "Failed to allocate image struct");
	game->img->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!game->img->img)
		exit_error(game, "Failed to create image");
	game->img->addr = mlx_get_data_addr(game->img->img, &game->img->bpp,
			&game->img->line_len, &game->img->endian);
	if (!game->img->addr)
		exit_error(game, "Failed to get image buffer");
}

void	init_game(t_game *game)
{
	init_screen(game);
	mlx_hook(game->win, 17, (1L << 17), close_handler, game);
	mlx_key_hook(game->win, key_handler, game);
	mlx_loop_hook(game->mlx, loop_handler, game);
	mlx_loop(game->mlx);
}
