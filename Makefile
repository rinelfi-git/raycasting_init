NAME = raycasting
CC = gcc
CARG = -Werror -Wextra -Wall
INCs = -I./include -I./lib/mlx
SRCs = ./src/main.c \
		./src/core/draw.c \
		./src/core/init.c \
		./src/core/put_pixel.c \
		./src/raycasting/texture.c
OBJs = $(SRCs:.c=.o)
LIBs = -L./lib/mlx -lmlx -L/usr/lib -lXext -lX11 -lm -lz
LIB_MLX = ./lib/mlx/libmlx.a

all: $(NAME)

$(NAME): $(OBJs) $(LIB_MLX)
	$(CC) $(OBJs) $(LIBs) -o $(NAME)

clean:
	rm -rf $(OBJs)
	rm -rf ./lib/mlx/*.o

fclean: clean
	rm -rf $(NAME)
	rm -rf ./lib/mlx/*.a

re: fclean all

%.o: %.c
	$(CC) $(CARG) -O3 $(INCs) -c $< -o $@

$(LIB_MLX) :
	make -C ./lib/mlx
