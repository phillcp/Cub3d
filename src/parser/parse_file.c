/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 18:18:30 by gude-and          #+#    #+#             */
/*   Updated: 2026/03/12 20:02:14 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	all_elements_parsed(t_game *game)
{
	if (!game->no_tex.path || !game->so_tex.path)
		return (0);
	if (!game->we_tex.path || !game->ea_tex.path)
		return (0);
	if (game->floor_color == -1 || game->ceiling_color == -1)
		return (0);
	return (1);
}

int	check_line_texpath(t_game *game, const char *line)
{
	int	i;
	int	spaces;

	i = 2;
	spaces = 0;
	if (!ft_isspace(line[i]))
		exit_errorfd(game, "Wrong texture path formating in map file");
	while (line[i + spaces] && ft_isspace(line[i + spaces]))
		spaces++;
	i += spaces;
	if (!line[i])
		exit_errorfd(game, "Wrong texture path formating in map file");
	return (spaces);
}

char	*read_file_path(t_game *game, const char *line)
{
	char	*path;
	int		last_char;
	int		spaces;

	spaces = check_line_texpath(game, line);
	path = ft_strdup(line + spaces + 2);
	if (!path)
		exit_errorfd(game, "Failed allocation while importing texture");
	last_char = ft_strlen(line) - 1;
	while (ft_isspace(line[last_char]))
		path[last_char--] = '\0';
	return (path);
}

void	parse_texture_path(t_game *game, char *line)
{
	if (line[0] == 'N' && line[1] == 'O' && !game->no_tex.path)
		game->no_tex.path = read_file_path(game, line);
	if (line[0] == 'S' && line[1] == 'O' && !game->no_tex.path)
		game->so_tex.path = read_file_path(game, line);
	if (line[0] == 'W' && line[1] == 'E' && !game->no_tex.path)
		game->we_tex.path = read_file_path(game, line);
	if (line[0] == 'E' && line[1] == 'A' && !game->no_tex.path)
		game->ea_tex.path = read_file_path(game, line);
	else
		exit_errorfd(game, "Invalid line in map file");
}

u_int32_t	create_rgb(u_int32_t t, u_int32_t r, u_int32_t g, u_int32_t b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	check_nmr_comma(const char *line, int i, int last)
{
	int	j;

	j = 0;
	if (!ft_isdigit(line[i + j]))
		return (-1);
	while (line[i + j] && ft_isdigit(line[i + j]))
		j++;
	if (!last)
	{
		if (!line[i + j] == ',')
			return (-1);
		j++;
	}
	return (j);
}

void	check_line_color(t_game *game, const char *line)
{
	int	i;
	int	check;

	i = 1;
	check = 0;
	if (!ft_isspace(line[i]))
		check = -1;
	while (line[i] && ft_isspace(line[i]))
		i++;
	check = check_nmr_comma(line, i, 0);
	if (check == -1)
		exit_errorfd(game, "Bad RGB value");
	i += check;
	check = check_nmr_comma(line, i, 0);
	if (check == -1)
		exit_errorfd(game, "Bad RGB value");
	i += check;
	check = check_nmr_comma(line, i, 1);
	if (check == -1)
		exit_errorfd(game, "Bad RGB value");
}

u_int32_t	read_rgb(t_game *game, const char *line)
{
	int			i;
	u_int32_t	r;
	u_int32_t	g;
	u_int32_t	b;

	check_line_color(game, line);
	r = 0;
	g = 0;
	b = 0;
	i = 1;
	while (line[i] && line[i] != ',' && ft_isdigit(line[i]))
		r = r * 10 + (line[i++] - 48);
	i++;
	while (line[i] && line[i] != ',' && ft_isdigit(line[i]))
		g = g * 10 + (line[i++] - 48);
	i++;
	while (line[i] && line[i] != ',' && ft_isdigit(line[i]))
		b = b * 10 + (line[i++] - 48);
	if (r > 255 || g > 255 || b > 255)
		exit_errorfd(game, "Bad RGB value");
	return (create_rgb(255, r, g, b));
}

void	parse_color(t_game *game, char *line)
{
	if (line[0] == 'F')
		game->floor_color = read_rgb(game, line);
	else if (line[0] == 'C')
		game->ceiling_color = read_rgb(game, line);
	else
		exit_errorfd(game, "Invalid line in map file");
}

void	parse_line(t_game *game, char *line)
{
	int	i;
	int	j;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (line[i])
		return ;
	j = 0;
	while (line[i + j] && !ft_isspace(line[i + j]))
		j++;
	if (j == 2)
		parse_texture_path(game, line + i);
	else if (j == 1)
		parse_color(game, line + i);
	else
		exit_errorfd(game, "Invalid map file");
}

static int	parse_elements_and_map(t_game *game, int fd)
{
	int		lines_read;
	char	*line;
	int		map_start;

	lines_read = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] != '\n' && !all_elements_parsed(game))
			parse_line(game, line);
		else if (line[0] != '\n' && all_elements_parsed(game))
		{
			map_start = 1;
			parse_map(game, fd, line); //confirmar que mapa tem de ter max_width em todas as rows para nao dar merda na validaçao
			break ;
		}
		ft_free(line);
		lines_read++;
	}
	if (!map_start)
		exit_errorfd(game, "Invalid map file");
	return (lines_read);
}

char	*get_data_addr(t_game *game, t_img *img)
{
	char	*addr;

	addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len, &img->endian);
	if (!addr)
		exit_error(game, "Failed to get data addr while importing texture");
	return (addr);
}

int	**new_matrix(t_game *game)
{
	int		**tex;
	int		y;

	tex = ft_calloc(TEXTURE_SIZE + 1, sizeof(int *));
	if (!tex)
		exit_error(game, "Failed allocation while getting new_tex");
	y = -1;
	while (++y < TEXTURE_SIZE)
	{
		tex[y] = ft_calloc(TEXTURE_SIZE, sizeof(int));
		if (!tex[y])
		{
			free_matrix((void **)tex);
			exit_error(game, "Failed allocation while getting new_tex");
		}
	}
	return (tex);
}

void	fill_matrix(t_img *tmp, int **texture, int height, int width)
{
	int				x;
	int				y;
	unsigned char	*c;

	y = -1;
	while (++y < height)
	{
		x = -1;
		while (++x < width)
		{
			c = (unsigned char *)tmp->addr + (y * tmp->line_len + (x * \
				(tmp->bpp / 8)));
			texture[y][x] = (unsigned int)(c[3] << 24 | c[2] << 16 \
				| c[1] << 8 | c[0]);
		}
	}
}

int	**load_tex(t_game *game, void *mlx, char *path)
{
	int		**tex;
	t_img	*tmp;
	int		img_height;
	int		img_width;

	if (!path)
		exit_error(game, "Missing path to texture");
	tmp = ft_calloc(1, sizeof(t_img));
	if (!tmp)
		exit_error(game, "Failed allocation while loading texture");
	tmp->img = mlx_xpm_file_to_image(mlx, path, &img_width, &img_height);
	if (!tmp->img)
		exit_error(game, "Failed to load texture image");
	tmp->addr = get_data_addr(game, tmp);
	tex = new_matrix(game);
	fill_matrix(tmp, tex, img_height, img_width);
	mlx_destroy_image(mlx, tmp->img);
	free(tmp);
	return (tex);
}

void	load_textures(t_game *game)
{
	game->no_tex.tex = load_tex(game, game->mlx, game->no_tex.path);
	game->so_tex.tex = load_tex(game, game->mlx, game->so_tex.path);
	game->we_tex.tex = load_tex(game, game->mlx, game->we_tex.path);
	game->ea_tex.tex = load_tex(game, game->mlx, game->ea_tex.path);
}

void	parse_cub_file(t_game *game, char *filename)
{
	int		fd;
	int		len;

	len = ft_strlen(filename);
	if (len < 4 || ft_strncmp(filename + len - 4, ".cub", 4) != 0)
		exit_error(game, "Invalid file extension. Must be .cub");
	game->open_fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_error(game, "Could not open file");
	parse_elements_and_map(game, fd); //check parse_map
	close(game->open_fd);
	load_textures(game);
	validate_map(game);
	return (1);
}
