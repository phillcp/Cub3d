/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 10:10:00 by gude-and          #+#    #+#             */
/*   Updated: 2026/03/18 10:10:00 by gude-and         ###   ########.fr       */
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

int	line_len_without_nl(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		len--;
	return (len);
}

void	update_map_width(t_map *map, char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len > map->width)
		map->width = len;
}

char	*build_padded_map_line(t_game *game, char *line)
{
	char	*row;
	int		line_len;

	line_len = line_len_without_nl(line);
	row = ft_calloc(game->map.width + 1, sizeof(char));
	if (!row)
		exit_errorfd(game, "Memory allocation failed in map grid");
	ft_memset(row, ' ', game->map.width);
	ft_memcpy(row, line, line_len);
	row[game->map.width] = '\0';
	return (row);
}
