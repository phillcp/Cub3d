/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 18:19:31 by gude-and          #+#    #+#             */
/*   Updated: 2026/02/04 18:19:32 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <sys/stat.h> // Para a função stat

int parse_texture(t_texture *texture, char *line, const char *identifier)
{
    char    **split;
    char    *path;
    struct stat   statbuf;

    // 1. Verificar se o identificador corresponde
    if (ft_strncmp(line, identifier, ft_strlen(identifier)) != 0)
        return (0);

    // 2. Separar a linha para obter o caminho
    split = ft_split(line, ' ');
    if (!split || !split[0] || !split[1] || split[2])
    {
        if (split) ft_free_split(split);
        return (exit_error("Invalid texture format."), 0);
    }

    path = ft_strtrim(split[1], "\n");
    ft_free_split(split);

    // 3. Validar o caminho
    // Verificar se a extensão é .xpm
    if (ft_strncmp(path + ft_strlen(path) - 4, ".xpm", 4) != 0)
    {
        free(path);
        return (exit_error("Texture file must be a .xpm file."), 0);
    }
    // Verificar se o arquivo existe e é legível
    if (stat(path, &statbuf) != 0)
    {
        free(path);
        return (exit_error("Texture file not found or inaccessible."), 0);
    }

    // 4. Armazenar o caminho validado na estrutura
    if (texture->path) // Se já foi carregado, é um erro
    {
        free(path);
        return (exit_error("Duplicate texture identifier."), 0);
    }
    texture->path = path;
    
    return (1);
}