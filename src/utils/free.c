/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 18:22:47 by gude-and          #+#    #+#             */
/*   Updated: 2026/02/04 18:37:23 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void free_game(t_game *game)
{
    if (game->no_tex.path)
        free(game->no_tex.path);
    if (game->so_tex.path)
        free(game->so_tex.path);
    if (game->we_tex.path)
        free(game->we_tex.path);
    if (game->ea_tex.path)
        free(game->ea_tex.path);

    // O mapa e outros elementos serão liberados aqui quando os implementarmos.

    // Inicializa os ponteiros para NULL para evitar double free
    memset(game, 0, sizeof(t_game));
}

void ft_free_split(char **split)
{
    int i;

    if (!split)
        return ;
    i = 0;
    while (split[i])
    {
        free(split[i]);
        i++;
    }
    free(split);
}
