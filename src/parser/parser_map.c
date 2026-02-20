/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:38:49 by gude-and          #+#    #+#             */
/*   Updated: 2026/02/18 17:58:02 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	if (!line || ft_strlen(line) == 0)
		return (0);
	while (line[i])
	{
		if (!ft_strchr(MAP_CHARS, line[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	update_map_width(t_map *map, char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len > map->width)
		map->width = len;
	return (1);
}

static char	**realloc_grid(char **old, int old_size, char *new_line)
{
	char	**new_grid;
	int		i;

	new_grid = malloc(sizeof(char *) * (old_size + 1));
	if (!new_grid)
		return (NULL);
	i = 0;
	while (i < old_size)
	{
		new_grid[i] = old[i];
		i++;
	}
	new_grid[i] = ft_strdup(new_line);
	if (!new_grid[i])
	{
		free_map_grid(new_grid, old_size);
		return (NULL);
	}
	free(old);
	return (new_grid);
}

static int	add_map_line(t_game *game, char *line)
{
	char	*clean;
	char	**new_grid;

	clean = line;
	if (clean[ft_strlen(clean) - 1] == '\n')
		clean[ft_strlen(clean) - 1] = '\0';
	if (!is_map_line(clean))
		return (exit_error("Invalid character in map"), 0);
	update_map_width(&game->map, clean);
	new_grid = realloc_grid(game->map.grid, game->map.height, clean);
	if (!new_grid)
		return (exit_error("Memory allocation failed"), 0);
	game->map.grid = new_grid;
	game->map.height++;
	return (1);
}

static int	process_line(t_game *game, char *line, int *found_empty)
{
	if (ft_strlen(line) == 0 || (ft_strlen(line) == 1 && line[0] == '\n'))
	{
		if (game->map.height > 0)
			*found_empty = 1;
		free(line);
		return (1);
	}
	if (*found_empty)
		return (free(line), exit_error("Map has empty line gap"), 0);
	if (!add_map_line(game, line))
		return (free(line), 0);
	free(line);
	return (1);
}

int	parse_map(t_game *game, int fd, char *first_line)
{
	char	*line;
	int		gnl_ret;
	int		found_empty;

	found_empty = 0;
	gnl_ret = 1;
	if (!process_line(game, first_line, &found_empty))
		return (0);
	while (1)
	{
		line = NULL;
		gnl_ret = get_next_line(fd, &line);
		if (gnl_ret <= 0)
		{
			if (line)
				free(line);
			break ;
		}
		if (!process_line(game, line, &found_empty))
			return (0);
	}
	if (game->map.height < 3)
		return (exit_error("Map too small"), 0);
	return (1);
}
