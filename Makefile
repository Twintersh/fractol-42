CC = gcc
NAME = fractol
LFT = libft
SRC= src/fractol.c src/draw.c src/hook.c
OBJ=$(SRC:.c=.o)
LFLAGS = -L mlx_linux -lmlx -lXext -lX11 -L libft -lft
CFLAGS = -Wall -Ofast -Wextra -Werror

all : $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -I/src/ -c $< -o $@

$(NAME) : $(OBJ)
	make -C mlx_linux
	make -C $(LFT)
	$(CC) $(CFLAGS) $(OBJ) $(LFLAGS) -o $(NAME)

clean :
	make -C mlx_linux clean
	make -C $(LFT) clean
	rm -rf src/*.o

fclean : clean
	make -C $(LFT) fclean
	rm -rf $(NAME)
	rm -rf $(NAME_BONUS)

run : all
	./$(NAME) $(ARG)

re : fclean all

reb : fclean bonus

debug : $(OBJ)
	make -C mlx_linux
	make -C $(LFT)
	$(CC) $(CFLAGS) -g3 $(OBJ) $(LFLAGS) -o $(NAME)

.PHONY : debug re fclean clean run all
