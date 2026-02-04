/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 18:20:19 by gude-and          #+#    #+#             */
/*   Updated: 2026/02/04 18:20:20 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int is_valid_rgb(int r, int g, int b)
{
    return (r >= 0 && r <= RGB_MAX && g >= 0 && g <= RGB_MAX && b >= 0 && b <= RGB_MAX);
}

int parse_color(int *color, char *line, const char *identifier)
{
    char    **split;
    char    **rgb_split;
    int     r, g, b;

    // 1. Verificar se o identificador corresponde
    if (ft_strncmp(line, identifier, ft_strlen(identifier)) != 0)
        return (0);

    // 2. Separar a linha para obter os valores RGB
    split = ft_split(line, ' ');
    if (!split || !split[0] || !split[1] || split[2])
    {
        if (split) ft_free_split(split);
        return (exit_error("Invalid color format."), 0);
    }

    rgb_split = ft_split(split[1], ',');
    ft_free_split(split);

    if (!rgb_split || !rgb_split[0] || !rgb_split[1] || !rgb_split[2] || rgb_split[3])
    {
        if (rgb_split) ft_free_split(rgb_split);
        return (exit_error("Color must have 3 RGB components separated by commas."), 0);
    }

    // 3. Converter para inteiros e validar
    r = ft_atoi(rgb_split[0]);
    g = ft_atoi(rgb_split[1]);
    b = ft_atoi(rgb_split[2]);
    ft_free_split(rgb_split);

    if (!is_valid_rgb(r, g, b))
        return (exit_error("RGB values must be between 0 and 255."), 0);

    // 4. Armazenar a cor no formato inteiro (0x00RRGGBB)
    if (*color != -1) // Verificar duplicata
        return (exit_error("Duplicate color identifier."), 0);
    
    *color = (r << 16) | (g << 8) | b;
    
    return (1);
}