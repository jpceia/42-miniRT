NAME		= miniRT

LIBFT_DIR	= ./libft

INC_DIR		= headers

SRC_DIR		= src
OBJ_DIR		= obj

SRCS		= $(shell find $(SRC_DIR) -name *.c -type f)
OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC			= gcc
RM			= rm -f

OS			= $(shell uname)

ifeq ($(OS), Linux)
	MLX_INC_DIR	= /usr/local/include
	MLX_DIR		= /usr/local/lib
	FLAG_OS		= -D OS_Linux
	FLAGS_MLX	= -Lmlx_Linux -lmlx_Linux -Imlx_linux -lXext -lX11 -lz
else
	MLX_INC_DIR	= ./minilibx_opengl_20191021
	MLX_DIR		= ./minilibx_opengl_20191021
	FLAGS_MLX	= -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
endif
FLAGS_WARN	= -Wall -Wextra -Werror
FLAGS_INC	= -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_INC_DIR)
FLAGS_DEBUG	= -g
FLAGS_OPT	= -O3
FLAGS_LIBFT = -L$(LIBFT_DIR) -lft
CFLAGS		= $(FLAGS_WARN) $(FLAGS_INC) $(FLAGS_OPT) $(FLAG_OS)
LDFLAGS		= $(FLAGS_LIBFT) $(FLAGS_MLX) $(FLAGS_OPT) -lm

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
ifneq ($(OS), Linux)
	$(MAKE) -C $(MLX_DIR)
endif
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $^ -o $@ $(LDFLAGS)

all: $(NAME)

clean:
ifneq ($(OS), Linux)
	$(MAKE) -C $(MLX_DIR) clean
endif
	$(MAKE) -C $(LIBFT_DIR) clean
	$(RM) -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re:	fclean all

# Debugging functions

debug:		CFLAGS += $(FLAGS_DEBUG)
debug:		LDFLAGS += $(FLAGS_DEBUG)
debug:		re

.PHONY:		all clean fclean re
