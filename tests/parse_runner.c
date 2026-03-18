#define main cub3d_main
#include "cub3d.h"
#undef main
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

typedef struct s_test
{
	const char	*name;
	const char	*content;
	const char	*path;
	const char	*suffix;
	int		expect_ok;
	int		expect_height;
	const char	*expect_first_row;
}t_test;

static void	init_game_struct(t_game *game)
{
	ft_memset(game, 0, sizeof(t_game));
	game->no_tex.path = NULL;
	game->so_tex.path = NULL;
	game->ea_tex.path = NULL;
	game->we_tex.path = NULL;
	game->no_tex.tex = NULL;
	game->so_tex.tex = NULL;
	game->ea_tex.tex = NULL;
	game->we_tex.tex = NULL;
	game->map.grid = NULL;
	game->map_filename = NULL;
	game->open_fd = -1;
	game->floor_color = -1;
	game->ceiling_color = -1;
	game->mlx = mlx_init();
}

static const char	*write_temp_file(const char *content, const char *suffix,
	char *out_path, size_t out_size)
{
	char		template[64];
	int		fd;
	ssize_t	written;
	int		suf_len;

	suf_len = suffix ? (int)strlen(suffix) : 0;
	snprintf(template, sizeof(template), "/tmp/cub3d_parse_XXXXXX%s",
		suffix ? suffix : "");
	fd = mkstemps(template, suf_len);
	if (fd == -1)
		return (NULL);
	written = write(fd, content, strlen(content));
	close(fd);
	if (written < 0)
		return (NULL);
	strncpy(out_path, template, out_size - 1);
	out_path[out_size - 1] = '\0';
	return (out_path);
}

static int	run_single_test(const t_test *t)
{
	t_game	game;
	const char	*path;
	char		path_buf[128];
	pid_t		pid;
	int		status;
	int		created;
	int		pass;

	created = 0;
	if (t->content)
	{
		path = write_temp_file(t->content, t->suffix ? t->suffix : ".cub",
			path_buf, sizeof(path_buf));
		created = 1;
	}
	else
		path = t->path;
	if (!path)
	{
		printf("[FAIL] %s (setup failed)\n", t->name);
		return (0);
	}
	pass = 1;
	if (t->expect_ok)
	{
		init_game_struct(&game);
		if (!game.mlx)
			pass = 0;
		else
		{
			parse_cub_file(&game, (char *)path);
			if (t->expect_height >= 0 && game.map.height != t->expect_height)
				pass = 0;
			if (pass && t->expect_first_row && game.map.grid
				&& strcmp(game.map.grid[0], t->expect_first_row) != 0)
				pass = 0;
			if (pass && t->expect_first_row && (!game.map.grid || !game.map.grid[0]))
				pass = 0;
		}
		free_game(&game);
	}
	else
	{
		pid = fork();
		if (pid == -1)
		{
			if (created)
				unlink(path);
			printf("[FAIL] %s (fork failed)\n", t->name);
			return (0);
		}
		if (pid == 0)
		{
			init_game_struct(&game);
			if (!game.mlx)
				_exit(EXIT_FAILURE);
			parse_cub_file(&game, (char *)path);
			free_game(&game);
			_exit(EXIT_SUCCESS);
		}
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
			pass = 0;
	}
	if (created)
		unlink(path);
	printf("[%s] %s (expected %s)\n", pass ? "PASS" : "FAIL", t->name,
		t->expect_ok ? "success" : "error");
	return (pass);
}

#define TEX_BLOCK \
	"NO ./textures/north.xpm\n" \
	"SO ./textures/south.xpm\n" \
	"WE ./textures/west.xpm\n" \
	"EA ./textures/east.xpm\n"

int	main(void)
{
	const t_test tests[] = {
		{ "valid minimal map",
			TEX_BLOCK
			"F 10,20,30\nC 40,50,60\n\n"
			"111\n1N1\n111\n",
			NULL, ".cub", 1, 3, "111" },
		{ "missing map section",
			TEX_BLOCK
			"F 10,20,30\nC 40,50,60\n\n",
			NULL, ".cub", 0, -1, NULL },
		{ "invalid map character",
			TEX_BLOCK
			"F 10,20,30\nC 40,50,60\n\n"
			"1X1\n1N1\n111\n",
			NULL, ".cub", 0, -1, NULL },
		{ "empty line gap in map",
			TEX_BLOCK
			"F 10,20,30\nC 40,50,60\n\n"
			"111\n\n1N1\n111\n",
			NULL, ".cub", 0, -1, NULL },
		{ "duplicate texture identifier",
			"NO ./textures/north.xpm\n"
			"NO ./textures/north.xpm\n"
			"SO ./textures/south.xpm\n"
			"WE ./textures/west.xpm\n"
			"EA ./textures/east.xpm\n"
			"F 10,20,30\nC 40,50,60\n\n"
			"111\n1N1\n111\n",
			NULL, ".cub", 0, -1, NULL },
		{ "invalid color format",
			TEX_BLOCK
			"F 10,20\nC 40,50,60\n\n"
			"111\n1N1\n111\n",
			NULL, ".cub", 0, -1, NULL },
		{ "wrong file extension",
			TEX_BLOCK
			"F 10,20,30\nC 40,50,60\n\n"
			"111\n1N1\n111\n",
			NULL, ".tmp", 0, -1, NULL },
		{ "missing player",
			TEX_BLOCK
			"F 10,20,30\nC 40,50,60\n\n"
			"111\n101\n111\n",
			NULL, ".cub", 0, -1, NULL },
		{ "missing texture file",
			"NO ./textures/missing.xpm\n"
			"SO ./textures/south.xpm\n"
			"WE ./textures/west.xpm\n"
			"EA ./textures/east.xpm\n"
			"F 10,20,30\nC 40,50,60\n\n"
			"111\n1N1\n111\n",
			NULL, ".cub", 0, -1, NULL },
		{ "map too small",
			TEX_BLOCK
			"F 10,20,30\nC 40,50,60\n\n"
			"11\n1N\n",
			NULL, ".cub", 0, -1, NULL },
		{ "invalid texture extension",
			"NO ./textures/north.png\n"
			"SO ./textures/south.xpm\n"
			"WE ./textures/west.xpm\n"
			"EA ./textures/east.xpm\n"
			"F 10,20,30\nC 40,50,60\n\n"
			"111\n1N1\n111\n",
			NULL, ".cub", 0, -1, NULL },
		{ "duplicate player",
			TEX_BLOCK
			"F 10,20,30\nC 40,50,60\n\n"
			"111\n1N1\n1S1\n111\n",
			NULL, ".cub", 0, -1, NULL },
		{ "open boundary",
			TEX_BLOCK
			"F 10,20,30\nC 40,50,60\n\n"
			"110\n1N1\n111\n",
			NULL, ".cub", 0, -1, NULL },
		{ "void adjacency",
			TEX_BLOCK
			"F 10,20,30\nC 40,50,60\n\n"
			"1111\n1N01\n1 11\n1111\n",
			NULL, ".cub", 0, -1, NULL },
		{ "nonexistent file path", NULL, "/tmp/does_not_exist.cub",
			NULL, 0, -1, NULL }
	};
	int		pass_count;
	int		total;
	int		i;

	total = (int)(sizeof(tests) / sizeof(tests[0]));
	pass_count = 0;
	i = 0;
	while (i < total)
	{
		pass_count += run_single_test(&tests[i]);
		i++;
	}
	printf("\nPassed %d/%d tests\n", pass_count, total);
	return (pass_count == total ? 0 : 1);
}
