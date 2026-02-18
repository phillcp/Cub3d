/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 18:18:30 by gude-and          #+#    #+#             */
/*   Updated: 2026/02/18 17:58:49 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*trim_whitespace(char *str)
{
	char	*end;

	while (*str == ' ' || *str == '\t')
		str++;
	if (*str == '\0')
		return (str);
	end = str + ft_strlen(str) - 1;
	while (end > str && (*end == ' ' || *end == '\t' || *end == '\n'))
		end--;
	*(end + 1) = '\0';
	return (str);
}

static int	parse_element(t_game *game, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (parse_texture(&game->no_tex, line, "NO"));
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (parse_texture(&game->so_tex, line, "SO"));
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (parse_texture(&game->we_tex, line, "WE"));
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (parse_texture(&game->ea_tex, line, "EA"));
	else if (ft_strncmp(line, "F ", 2) == 0)
		return (parse_color(&game->floor_color, line, "F"));
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (parse_color(&game->ceiling_color, line, "C"));
	return (-1);
}

static int	all_elements_parsed(t_game *game)
{
	if (!game->no_tex.path || !game->so_tex.path)
		return (0);
	if (!game->we_tex.path || !game->ea_tex.path)
		return (0);
	if (game->floor_color == -1 || game->ceiling_color == -1)
		return (0);
	return (1);
}

static int	parse_elements_and_map(t_game *game, int fd)
{
	char	*line;
	char	*trimmed;
	int		ret;

	line = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if (!all_elements_parsed(game))
		{
			trimmed = trim_whitespace(line);
			if (ft_strlen(trimmed) == 0)
			{
				free(line);
				line = NULL;
				continue ;
			}
			ret = parse_element(game, trimmed);
			if (ret == 0)
				return (free(line), 0);
			if (ret == -1)
				return (free(line), exit_error("Invalid element in file"), 0);
			free(line);
			continue ;
		}
		if (ft_strlen(line) == 0 || (ft_strlen(line) == 1 && line[0] == '\n'))
		{
			free(line);
			line = NULL;
			continue ;
		}
		trimmed = ft_strdup(line);
		free(line);
		if (!trimmed)
			return (exit_error("Memory allocation failed"), 0);
		if (!parse_map(game, fd, trimmed))
			return (0);
		return (1);
	}
	if (line)
		free(line);
	if (!all_elements_parsed(game))
		return (exit_error("Missing texture or color element"), 0);
	return (exit_error("Map not found in file"), 0);
}

int	parse_cub_file(t_game *game, char *filename)
{
	int		fd;
	int		len;

	len = ft_strlen(filename);
	if (len < 4 || ft_strncmp(filename + len - 4, ".cub", 4) != 0)
		return (exit_error("Invalid file extension. Must be .cub"), 0);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (exit_error("Could not open file"), 0);
	if (!parse_elements_and_map(game, fd))
	{
		close(fd);
		return (0);
	}
	close(fd);
	if (!validate_map(game))
		return (0);
	if (!init_player_from_map(game))
		return (0);
	return (1);
}
