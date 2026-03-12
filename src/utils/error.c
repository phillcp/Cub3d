/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 18:22:14 by gude-and          #+#    #+#             */
/*   Updated: 2026/03/12 19:18:00 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exit_errorfd(t_game *game, char *message)
{
	ft_putendl_fd("Error\n", 2);
	ft_putendl_fd(message, 2);
	close(game->open_fd);
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
