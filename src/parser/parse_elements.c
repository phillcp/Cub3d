/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 19:45:42 by gude-and          #+#    #+#             */
/*   Updated: 2026/03/18 19:47:44 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*read_file_path(t_game *game, char *line)
{
	char	*path;
	int		i;
	int		start;
	int		end;

	i = 2;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (!line[i])
		exit_errorfd(game, "Missing texture path");
	start = i;
	while (line[i] && !ft_isspace(line[i]))
		i++;
	end = i;
	path = ft_substr(line, start, end - start);
	if (!path)
		exit_errorfd(game, "Failed allocation for texture path");
	return (path);
}

void	parse_texture_path(t_game *game, char *line)
{
	if (line[0] == 'N' && line[1] == 'O' && !game->no_tex.path)
		game->no_tex.path = read_file_path(game, line);
	else if (line[0] == 'S' && line[1] == 'O' && !game->so_tex.path)
		game->so_tex.path = read_file_path(game, line);
	else if (line[0] == 'W' && line[1] == 'E' && !game->we_tex.path)
		game->we_tex.path = read_file_path(game, line);
	else if (line[0] == 'E' && line[1] == 'A' && !game->ea_tex.path)
		game->ea_tex.path = read_file_path(game, line);
	else
		exit_errorfd(game, "Duplicate or invalid texture identifier");
}

u_int32_t	create_rgb(u_int32_t t, u_int32_t r, u_int32_t g, u_int32_t b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

static u_int32_t	read_rgb(t_game *game, char *line)
{
	int			i;
	u_int32_t	rgb[3];
	int			count;

	i = 1;
	count = 0;
	while (count < 3)
	{
		while (line[i] && (ft_isspace(line[i]) || line[i] == ','))
			i++;
		if (!ft_isdigit(line[i]))
			exit_errorfd(game, "Invalid RGB format");
		rgb[count] = 0;
		while (ft_isdigit(line[i]))
			rgb[count] = rgb[count] * 10 + (line[i++] - '0');
		if (rgb[count] > 255)
			exit_errorfd(game, "RGB value out of range");
		count++;
	}
	return (create_rgb(255, rgb[0], rgb[1], rgb[2]));
}

void	parse_color(t_game *game, char *line)
{
	if (line[0] == 'F' && (int)game->floor_color == -1)
		game->floor_color = read_rgb(game, line);
	else if (line[0] == 'C' && (int)game->ceiling_color == -1)
		game->ceiling_color = read_rgb(game, line);
	else
		exit_errorfd(game, "Duplicate or invalid color identifier");
}
