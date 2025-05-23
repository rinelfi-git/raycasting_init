NAME = cub3D
CC = gcc
CARG = -Werror -Wextra -Wall
INCs = -I./include -I./lib/mlx
SRCs =  ./src/check_error/get_next_line/get_next_line_utils.c \
		./src/check_error/get_next_line/get_next_line.c \
		./src/check_error/arg_error.c \
		./src/check_error/check_lock.c \
		./src/check_error/check_map.c \
		./src/check_error/data_init.c \
		./src/check_error/init_check.c \
		./src/core/draw.c \
		./src/core/init.c \
		./src/core/put_pixel.c \
		./src/raycasting/collision_detector1.c \
		./src/raycasting/collision_detector2.c \
		./src/raycasting/dda1.c \
		./src/raycasting/dda2.c \
		./src/raycasting/draw_wall.c \
		./src/raycasting/event_listener.c \
		./src/raycasting/player_movement1.c \
		./src/raycasting/player_movement2.c \
		./src/raycasting/texture.c \
		./src/tools/free.c \
		./src/tools/ft_split.c \
		./src/tools/map_utils.c \
		./src/tools/size.c \
		./src/tools/utils1.c \
		./src/tools/utils2.c \
		./src/main.c
OBJs = $(SRCs:.c=.o)
LIBs = -L./lib/mlx -lmlx -L/usr/lib -lXext -lX11 -lm -lz
LIB_MLX = ./lib/mlx/libmlx.a

$(NAME): $(OBJs) $(LIB_MLX)
	$(CC) $(OBJs) $(LIBs) -o $(NAME)

all: $(NAME)

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
