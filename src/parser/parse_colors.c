/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 18:20:19 by gude-and          #+#    #+#             */
/*   Updated: 2026/02/18 17:38:25 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_rgb(int r, int g, int b)
{
	if (r < 0 || r > RGB_MAX)
		return (0);
	if (g < 0 || g > RGB_MAX)
		return (0);
	if (b < 0 || b > RGB_MAX)
		return (0);
	return (1);
}

static int	extract_rgb(char **rgb, int *r, int *g, int *b)
{
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
	{
		ft_free_split(rgb);
		return (exit_error("Color needs 3 RGB values"), 0);
	}
	*r = ft_atoi(rgb[0]);
	*g = ft_atoi(rgb[1]);
	*b = ft_atoi(rgb[2]);
	ft_free_split(rgb);
	if (!is_valid_rgb(*r, *g, *b))
		return (exit_error("RGB values must be 0-255"), 0);
	return (1);
}

int	parse_color(int *color, char *line, const char *id)
{
	char	**split;
	char	**rgb;
	int		r;
	int		g;
	int		b;

	if (ft_strncmp(line, id, ft_strlen(id)) != 0)
		return (0);
	split = ft_split(line, ' ');
	if (!split || !split[0] || !split[1] || split[2])
	{
		ft_free_split(split);
		return (exit_error("Invalid color format"), 0);
	}
	rgb = ft_split(split[1], ',');
	ft_free_split(split);
	if (!extract_rgb(rgb, &r, &g, &b))
		return (0);
	if (*color != -1)
		return (exit_error("Duplicate color identifier"), 0);
	*color = (r << 16) | (g << 8) | b;
	return (1);
}
