NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
MLX_FLAGS = -lmlx -lXext -lX11 -lm

INCLUDES_DIR = includes/
LIBFT_DIR = lib/libft/
LIBFT_INC_DIR = $(LIBFT_DIR)inc/
LIBFT_BIN_DIR = $(LIBFT_DIR)bin/
MLX_DIR = lib/minilibx-linux/

INCLUDES = -I$(INCLUDES_DIR) -I$(LIBFT_INC_DIR) -I$(MLX_DIR)
LIBS = -L$(LIBFT_BIN_DIR) -lft -L$(MLX_DIR) $(MLX_FLAGS)

SRCS = src/main.c \
		src/parser/parse_file.c \
		src/parser/parse_textures.c \
		src/parser/parse_colors.c \
		src/parser/parser_map.c \
		src/parser/validate_map.c \
		src/parser/init_player.c \
		src/utils/error.c \
		src/utils/free.c \
		src/game/init_game.c \
		src/game/3d.c \
		src/game/mlx_raper.c \
		src/game/movement.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT_DIR)
	@make -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@make -C $(LIBFT_DIR) clean
	@make -C $(MLX_DIR) clean
	rm -f $(OBJS)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
