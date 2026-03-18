/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 18:18:30 by gude-and          #+#    #+#             */
/*   Updated: 2026/03/18 19:47:41 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	all_elements_parsed(t_game *game)
{
	if (!game->no_tex.path || !game->so_tex.path)
		return (0);
	if (!game->we_tex.path || !game->ea_tex.path)
		return (0);
	if ((int)game->floor_color == -1 || (int)game->ceiling_color == -1)
		return (0);
	return (1);
}

void	parse_line(t_game *game, char *line)
{
	int	i;
	int	j;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (!line[i])
		return ;
	j = 0;
	while (line[i + j] && !ft_isspace(line[i + j]))
		j++;
	if (j == 2)
		parse_texture_path(game, line + i);
	else if (j == 1)
		parse_color(game, line + i);
	else
	{
		free(line);
		get_next_line(game->open_fd, &line, 1);
		exit_errorfd(game, "Invalid map file line");
	}
}

static void	parse_elements_and_map(t_game *game)
{
	char	*line;
	int		lines_read;
	int		map_start;

	lines_read = 0;
	map_start = 0;
	while (get_next_line(game->open_fd, &line, 0) > 0)
	{
		if (line[0] && line[0] != '\n' && !all_elements_parsed(game))
			parse_line(game, line);
		else if (line[0] && line[0] != '\n' && all_elements_parsed(game))
		{
			map_start = 1;
			parse_map(game, line, lines_read);
			break ;
		}
		ft_free(line);
		lines_read++;
	}
	if (!map_start)
		exit_errorfd(game, "No map in file");
}

void	parse_cub_file(t_game *game, char *filename)
{
	int		len;
	char	*line;

	len = ft_strlen(filename);
	if (len < 4 || ft_strncmp(filename + len - 4, ".cub", 4) != 0)
		exit_error(game, "Invalid file extension. Must be .cub");
	game->map_filename = ft_strdup(filename);
	if (!game->map_filename)
		exit_error(game, "Failed to save map filename");
	game->open_fd = open(filename, O_RDONLY);
	if (game->open_fd < 0)
		exit_error(game, "Could not open file");
	parse_elements_and_map(game);
	if (game->open_fd >= 0)
	{
		line = NULL;
		get_next_line(game->open_fd, &line, 1);
		close(game->open_fd);
		game->open_fd = -1;
	}
	load_textures(game);
	validate_map(game);
}
