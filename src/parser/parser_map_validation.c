/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map_validation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 10:20:00 by gude-and          #+#    #+#             */
/*   Updated: 2026/03/18 10:20:00 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	validate_line_content(t_game *game, char *line, int len)
{
	char	*clean;

	clean = ft_substr(line, 0, len);
	if (!clean || !is_map_line(clean))
	{
		free(clean);
		free(line);
		exit_errorfd(game, "Invalid character in map or allocation failed");
	}
	update_map_width(&game->map, clean);
	game->map.height++;
	free(clean);
}

void	validate_map_line(t_game *game, char *line, int *found_empty)
{
	int	len;

	len = line_len_without_nl(line);
	if (len == 0)
	{
		if (game->map.height > 0)
			*found_empty = 1;
		return ;
	}
	if (*found_empty)
	{
		free(line);
		exit_errorfd(game, "Map has empty line gap");
	}
	validate_line_content(game, line, len);
}
