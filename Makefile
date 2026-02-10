NAME = miniRT

CC = cc
CFLAGS = -Wall -Wextra -Werror

# ================= FILES =================

SRCS = \
	src/main.c \
	src/parser/parser.c \
	src/parser/parser_objects.c \
	src/parser/parser_utils.c \
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
	@echo "$(G)[SUCCESS]$(NC) miniRT compiled!"
$(NAME): $(OBJS) $(LIBFT) $(MLX42_LIB)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX42_LIB) $(MLX42_FLAGS) -o $(NAME)
$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# ================= LIB RULES =============

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

$(MLX42_LIB):
	@cmake -S $(MLX42_DIR) -B $(MLX42_DIR)/build
	@cmake --build $(MLX42_DIR)/build

# ================= CLEAN =================

G = \033[0;32m
R = \033[0;31m
Y = \033[0;33m
B = \033[0;34m
NC = \033[0m

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@rm -rf $(OBJDIR)
	@echo "$(Y)[CLEAN]$(NC) Objects deleted!"

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@rm -f $(NAME)
	@echo "$(R)[FCLEAN]$(NC) $(NAME) has been deleted!"

re: fclean all

v: $(NAME)
	valgrind --leak-check=full --track-fds=yes ./$(NAME) scene.rt                        

.PHONY: all clean fclean re v
