CC = gcc
NAME = fractol
NAME_BONUS = fractol_bonus
LFT = libft
SRC= src/fractol.c src/draw.c src/hook.c
OBJ=$(SRC:.c=.o)
SRC_BONUS= src/fractol_bonus.c \
			src/draw_bonus.c \
			src/hook_bonus.c
OBJ_BONUS=$(SRC_BONUS:.c=.o)

LFLAGS = -L mlx_linux -lmlx -lXext -lX11 -L libft -lft
CFLAGS = -Wall -Ofast -Wextra -Werror

all : $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -I/src/ -c $< -o $@

$(NAME) : $(OBJ)
	make -C mlx_linux
	make -C $(LFT)
	$(CC) $(CFLAGS) $(OBJ) $(LFLAGS) -o $(NAME)

run : $(NAME)
	./$(NAME) mandelbrot

clean :
	make -C mlx_linux clean
	make -C $(LFT) clean
	rm -rf src/*.o

fclean : clean
	make -C $(LFT) fclean
	rm -rf $(NAME)
	rm -rf $(NAME_BONUS)

re : fclean all

reb : fclean bonus

bonus : $(NAME_BONUS)

$(NAME_BONUS) : $(OBJ_BONUS)
	make -C mlx_linux
	make -C $(LFT)
	$(CC) $(CFLAGS) -lm $(OBJ_BONUS) $(LFLAGS) -o $(NAME_BONUS)

debug : $(OBJ)
	make -C mlx_linux
	make -C $(LFT)
	$(CC) $(CFLAGS) -g3 $(OBJ) $(LFLAGS) -o $(NAME)

.PHONY : debug bonus re fclean clean run all
