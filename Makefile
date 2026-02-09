NAME = miniRT

CC = cc
CFLAGS = -Wall -Wextra -Werror

# ================= FILES =================

SRCS = \
	src/main.c \
	src/parser/parser.c \
	utils/parser_utils.c \
	utils/error_exit.c

OBJDIR = obj
OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

# ================= LIBFT =================

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# ================= MLX42 =================

MLX42_DIR = MLX42
MLX42_LIB = $(MLX42_DIR)/build/libmlx42.a

MLX42_FLAGS = -ldl -lglfw -pthread -lm

# ================= INCLUDES ==============

INCLUDES = \
	-I include \
	-I $(LIBFT_DIR) \
	-I $(MLX42_DIR)/include

# ================= RULES =================

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX42_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX42_LIB) $(MLX42_FLAGS) -o $(NAME)

$(OBJDIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# ================= LIB RULES =============

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX42_LIB):
	cmake -S $(MLX42_DIR) -B $(MLX42_DIR)/build
	cmake --build $(MLX42_DIR)/build

# ================= CLEAN =================

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJDIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

v:
	valgrind --leak-check=full --track-fds=yes ./$(NAME)

.PHONY: all clean fclean re v
