/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 18:19:31 by gude-and          #+#    #+#             */
/*   Updated: 2026/02/18 17:37:49 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	validate_path(char *path)
{
	struct stat	statbuf;
	int			len;

	len = ft_strlen(path);
	if (len < 4 || ft_strncmp(path + len - 4, ".xpm", 4) != 0)
	{
		free(path);
		return (exit_error("Texture file must be .xpm"), 0);
	}
	if (stat(path, &statbuf) != 0)
	{
		free(path);
		return (exit_error("Texture file not found"), 0);
	}
	return (1);
}

int	parse_texture(t_texture *tex, char *line, const char *id)
{
	char	**split;
	char	*path;

	if (ft_strncmp(line, id, ft_strlen(id)) != 0)
		return (0);
	split = ft_split(line, ' ');
	if (!split || !split[0] || !split[1] || split[2])
	{
		ft_free_split(split);
		return (exit_error("Invalid texture format"), 0);
	}
	path = ft_strtrim(split[1], "\n");
	ft_free_split(split);
	if (!path)
		return (exit_error("Memory allocation failed"), 0);
	if (!validate_path(path))
		return (0);
	if (tex->path)
	{
		free(path);
		return (exit_error("Duplicate texture identifier"), 0);
	}
	tex->path = path;
	return (1);
}
