NAME	=	cub3d
CC		=	@cc
AR		=	@ar rcs
CFLAGS	=	-Wall -Wextra -Werror -MMD -MP -g
VLGRIND =	--suppressions=./readline.supp --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes

SRC_DIR	=	src/
INC_DIR	=	inc/
LIB_DIR	=	lib/
OBJ_DIR	=	obj/
DEP_DIR	=	dep/
LIBFT_DIR = $(LIB_DIR)libft/
MLX_DIR   = $(LIB_DIR)minilibx-linux/

SRC 	=	main.c \
			
SRCS	= $(addprefix $(SRC_DIR), $(SRC))
OBJS	= $(patsubst $(SRC_DIR)%, $(OBJ_DIR)%,$(SRCS:.c=.o))
DEPS	= $(patsubst $(SRC_DIR)%, $(DEP_DIR)%,$(SRCS:.c=.d))

LIBFT	 = $(LIBFT_DIR)bin/libft.a
INC_DIRS = $(INC_DIR)
INC_DIRS += $(LIBFT_DIR)$(INC_DIR)
INCS	 = $(addprefix -I, $(INC_DIRS))

MLX 	 = -L$(MLX_DIR) -lmlx -lX11 -lXext -lm
INCS	+= -I$(MLX_DIR)

RDLINE_FLAG = -lreadline
# INCS	+= -I/usr/include/readline

RESET	= \033[0m
BOLD	= \033[1m
RED		= \033[31m
GREEN	= \033[32m
YELLOW	= \033[33m
BLUE	= \033[34m


all: $(NAME)

$(OBJ_DIR) $(DEP_DIR):
	@mkdir -p $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@) $(dir $(DEP_DIR)$*.d)
	$(CC) $(CFLAGS) ${INCS} -c $< -o $@ -MF $(DEP_DIR)$*.d || { echo "Failed to create obj/dep"; exit 1;}
	@echo "File $< compiled"

$(LIBFT):
	@echo "Building libft"
	@$(MAKE) -s -C $(LIBFT_DIR) all

$(MLX):
	@echo "Building minilibx"
	@$(MAKE) -s -C $(MLX_DIR) all

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	@echo "Creating program"
	$(CC) $(CFLAGS) ${INCS} $(OBJS) $(LIBFT) $(MLX) -o $@ || { echo "Failed to create program"; exit 1; }
	@echo "Program compiled succesfully"

valgrind: $(NAME)
	valgrind $(VLGRIND) ./$(NAME)

mlx:
	@echo "Building minilibx"
	@$(MAKE) -C $(MLX_DIR)

libft:
	@echo "Building libft"
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	@if [ -d $(OBJ_DIR) ] || [ -d $(DEP_DIR) ]; then \
		echo "Cleaning"; \
		rm -rf $(OBJ_DIR) $(DEP_DIR); \
		echo "Clean"; \
	else \
		echo "No objs or deps to clean"; \
	fi

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	
re: fclean all

.PHONY: all re clean fclean mlx libft

-include ${DEPS}
