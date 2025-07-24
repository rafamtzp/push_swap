NAME = push_swap
LIBFT = libft/libft.a
LIBFT_DIR = libft
FT_PRINTF = ft_printf/libftprintf.a
FT_PRINTF_DIR = ft_printf

SRC = push_swap.c prep_args.c prep_helpers.c list_helpers.c reverse_rotations.c rotations.c \
	  sort.c swaps_and_pushes.c

OBJ = $(SRC:.c=.o)
CC = cc
CFLAGS = -Wall -Werror -Wextra -g

all: $(LIBFT) $(FT_PRINTF) $(NAME)

$(LIBFT):
	@make -C libft

$(FT_PRINTF):
	@make -C ft_printf

$(NAME): $(OBJ) $(LIBFT) $(FT_PRINTF)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft -L$(FT_PRINTF_DIR) -lftprintf -o $(NAME)

clean:
	@make -C $(LIBFT_DIR) clean
	@make -C $(FT_PRINTF_DIR) clean
	rm -f $(OBJ)

fclean:
	@make -C $(LIBFT_DIR) fclean
	@make -C $(FT_PRINTF_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re