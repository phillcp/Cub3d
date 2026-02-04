# Makefile for cub3D

NAME = cub3d

# Compilers and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
MLX_FLAGS = -lmlx -lXext -lX11 # Para Linux
# MLX_FLAGS = -lmlx -framework OpenGL -framework AppKit # Para macOS

# --- SEÇÃO CORRIGIDA ---
# Directories
INCLUDES_DIR = includes/
LIBFT_DIR = lib/libft/
LIBFT_INC_DIR = $(LIBFT_DIR)inc/  # Caminho para os headers da libft
LIBFT_BIN_DIR = $(LIBFT_DIR)bin/  # Caminho para a libft.a compilada
MLX_DIR = lib/minilibx-linux/

# Includes (para o COMPILADOR encontrar os .h)
INCLUDES = -I$(INCLUDES_DIR) -I$(LIBFT_INC_DIR) -I$(MLX_DIR)

# Libraries (para o LINKER encontrar os .a)
LIBS = -L$(LIBFT_BIN_DIR) -lft -L$(MLX_DIR) $(MLX_FLAGS)
# --- FIM DA SEÇÃO CORRIGIDA ---


# Source files
SRCS = src/main.c \
		src/parser/parse_file.c \
		src/parser/parse_textures.c \
		src/parser/parse_colors.c \
		src/utils/error.c \
		src/utils/free.c

# Object files
OBJS = $(SRCS:.c=.o)

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT_DIR) # Garante que a libft seja compilada antes de linkar
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
