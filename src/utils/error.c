/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 18:22:14 by gude-and          #+#    #+#             */
/*   Updated: 2026/03/15 17:28:59 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exit_errorfd(t_game *game, char *message)
{
	char	*line;

	ft_putendl_fd("Error\n", 2);
	ft_putendl_fd(message, 2);
	if (game && game->open_fd >= 0 && game->open_fd < FD_MAX)
	{
		line = NULL;
		get_next_line(game->open_fd, &line, 1);
	}
	if (game && game->open_fd >= 0)
	{
		close(game->open_fd);
		game->open_fd = -1;
	}
	free_game(game);
	exit(EXIT_FAILURE);
}

void	exit_error(t_game *game, char *message)
{
	ft_putendl_fd("Error\n", 2);
	ft_putendl_fd(message, 2);
	free_game(game);
	exit(EXIT_FAILURE);
}
