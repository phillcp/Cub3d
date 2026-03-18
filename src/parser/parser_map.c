/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:38:49 by gude-and          #+#    #+#             */
/*   Updated: 2026/03/15 17:33:18 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	first_map_pass(t_game *game, char *first_line)
{
	char	*line;
	int		found_empty;
	int		gnl_ret;

	found_empty = 0;
	validate_map_line(game, first_line, &found_empty);
	free(first_line);
	while (1)
	{
		line = NULL;
		gnl_ret = get_next_line(game->open_fd, &line, 0);
		if (gnl_ret <= 0)
		{
			if (line)
				free(line);
			break ;
		}
		validate_map_line(game, line, &found_empty);
		free(line);
	}
}

static void	skip_lines_before_map(t_game *game, int map_start_line)
{
	char	*line;
	int		i;

	i = 0;
	while (i < map_start_line)
	{
		line = NULL;
		if (get_next_line(game->open_fd, &line, 0) <= 0)
			exit_errorfd(game, "Unexpected end of file before map");
		free(line);
		i++;
	}
}

static void	second_map_pass(t_game *game)
{
	char	*line;
	int		y;

	game->map.grid = ft_calloc(game->map.height + 1, sizeof(char *));
	if (!game->map.grid)
		exit_errorfd(game, "Memory allocation failed in map grid");
	y = 0;
	while (y < game->map.height)
	{
		line = NULL;
		if (get_next_line(game->open_fd, &line, 0) <= 0)
			exit_errorfd(game, "Unexpected end of file while reading map");
		game->map.grid[y] = build_padded_map_line(game, line);
		free(line);
		y++;
	}
}

int	parse_map(t_game *game, char *first_line, int map_start_line)
{
	first_map_pass(game, first_line);
	if (game->map.height < 3 || game->map.width < 3)
		exit_errorfd(game, "Map too small");
	if (game->open_fd >= 0)
	{
		get_next_line(game->open_fd, NULL, 1);
		close(game->open_fd);
		game->open_fd = -1;
	}
	game->open_fd = open(game->map_filename, O_RDONLY);
	if (game->open_fd < 0)
		exit_errorfd(game, "Could not reopen map file");
	skip_lines_before_map(game, map_start_line);
	second_map_pass(game);
	return (1);
}
