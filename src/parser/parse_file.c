/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 18:18:30 by gude-and          #+#    #+#             */
/*   Updated: 2026/02/04 18:36:12 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Função auxiliar para remover espaços em branco no início e fim
static char *trim_whitespace(char *str)
{
    char *end;

    while ((*str == ' ' || *str == '\t'))
        str++;
    if (*str == 0)
        return (str);
    end = str + strlen(str) - 1;
    while (end > str && (*end == ' ' || *end == '\t'))
        end--;
    *(end + 1) = '\0';
    return (str);
}

int parse_cub_file(t_game *game, char *filename)
{
    int     fd;
    char    *line;
    int     ret;

    // 1. Verificar extensão do arquivo
    if (ft_strncmp(filename + ft_strlen(filename) - 4, ".cub", 4) != 0)
        return (exit_error("Invalid file extension. Must be .cub"), 0);

    // 2. Abrir o arquivo
    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (exit_error("Could not open file."), 0);

    // 3. Ler linha por linha
    while (get_next_line(fd, &line) > 0)
    {
        char *trimmed_line = trim_whitespace(line);

        // Pular linhas vazias
        if (strlen(trimmed_line) == 0)
        {
            free(line);
            continue;
        }

        // Identificar o elemento e chamar o parser correspondente
        if (ft_strncmp(trimmed_line, "NO ", 3) == 0)
            ret = parse_texture(&game->no_tex, trimmed_line, "NO");
        else if (ft_strncmp(trimmed_line, "SO ", 3) == 0)
            ret = parse_texture(&game->so_tex, trimmed_line, "SO");
        else if (ft_strncmp(trimmed_line, "WE ", 3) == 0)
            ret = parse_texture(&game->we_tex, trimmed_line, "WE");
        else if (ft_strncmp(trimmed_line, "EA ", 3) == 0)
            ret = parse_texture(&game->ea_tex, trimmed_line, "EA");
        else if (ft_strncmp(trimmed_line, "F ", 2) == 0)
            ret = parse_color(&game->floor_color, trimmed_line, "F");
        else if (ft_strncmp(trimmed_line, "C ", 2) == 0)
            ret = parse_color(&game->ceiling_color, trimmed_line, "C");
        else
        {
            // Por enquanto, vamos considerar qualquer outra coisa como erro.
            // O parsing do mapa virá depois.
            free(line);
            return (exit_error("Invalid element in .cub file."), 0);
        }

        free(line);
        if (!ret)
            return (0); // O erro já foi impresso pela função de parsing
    }
    close(fd);

    // 4. Validação final (básica por enquanto)
    if (!game->no_tex.path || !game->so_tex.path || !game->we_tex.path || !game->ea_tex.path)
        return (exit_error("Missing one or more texture paths."), 0);
    if (game->floor_color == -1 || game->ceiling_color == -1)
        return (exit_error("Missing floor or ceiling color."), 0);

    return (1); // Sucesso
}
