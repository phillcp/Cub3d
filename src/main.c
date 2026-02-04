/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 15:21:33 by fiheaton          #+#    #+#             */
/*   Updated: 2026/02/04 19:08:43 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#include "cub3d.h"

int main(int argc, char **argv)
{
    t_game  game;

    if (argc != 2)
    {
        exit_error("Usage: ./cub3d <map.cub>");
    }

    // Inicializa a estrutura do jogo com valores seguros
    memset(&game, 0, sizeof(t_game));

    // --- CORREÇÃO AQUI ---
    // Inicializa cores com um valor inválido (-1) para a verificação de duplicata funcionar
    game.floor_color = -1;
    game.ceiling_color = -1;
    // --- FIM DA CORREÇÃO ---

    if (!parse_cub_file(&game, argv[1]))
    {
        free_game(&game);
        return (1);
    }

    // Se chegamos aqui, o parsing foi bem-sucedido!
    printf("Parsing successful!\n");
    printf("NO texture: %s\n", game.no_tex.path);
    printf("SO texture: %s\n", game.so_tex.path);
    printf("WE texture: %s\n", game.we_tex.path);
    printf("EA texture: %s\n", game.ea_tex.path);
    printf("Floor color: %d\n", game.floor_color);
    printf("Ceiling color: %d\n", game.ceiling_color);

    free_game(&game);
    return (0);
}
