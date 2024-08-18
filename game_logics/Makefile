# Nombre del ejecutable
NAME = so_long

# Compilador y opciones
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3
INCLUDES = -I./include -I../printf/libft -I../printf
LIBS = -L../printf -lftprintf -L../printf/libft -lft -L../minilibx-linux -lmlx_Linux -lXext -lX11 -lm

# Archivos fuente y objetos
SRCS = cargar_imagen.c \
       ft_utils.c \
       mapa_draw.c \
       mapa_movement.c \
       mapa_read.c \
       maps_error.c \
       maps_practical.c \
       so_long.c
OBJS = $(SRCS:%.c=obj/%.o)

# Reglas
all: libft libftprintf $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME) $(LIBS)

obj/%.o: %.c
	mkdir -p obj
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

libft:
	make -C ../printf/libft

libftprintf:
	make -C ../printf

clean:
	make -C ../printf/libft clean
	make -C ../printf clean
	rm -f $(OBJS)
	rm -rf obj

fclean: clean
	make -C ../printf/libft fclean
	make -C ../printf fclean
	rm -f $(NAME)

re: fclean all
