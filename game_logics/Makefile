# Nombre del ejecutable
NAME = so_long

# Compilador y opciones
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I./include -I../printf/libft -I../printf
LIBS = -L../printf -lftprintf -L../printf/libft -lft -L../minilibx-linux -lmlx_Linux -lXext -lX11 -lm

# Archivos fuente y objetos
SRCS = cargar_imagen.c \
       ft_utils.c \
       mapa_draw.c \
       mapa_movement.c \
       mapa_read.c \
       maps_error.c \
       ft_utils_maps.c \
       maps_practical.c \
       so_long.c 

# Crear la lista de objetos a partir de los archivos fuente
OBJS = $(SRCS:%.c=obj/%.o)

# Directorios de compilación
OBJ_DIR = obj

# Reglas
all: libft libftprintf minilibx $(NAME)

# Regla para compilar el ejecutable
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME) $(LIBS)

# Regla para compilar cada archivo fuente en un archivo objeto
$(OBJ_DIR)/%.o: %.c
	mkdir -p $(OBJ_DIR)   # Crea el directorio de objetos si no existe
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Reglas para compilar las bibliotecas externas
libft:
	make -C ../printf/libft

libftprintf:
	make -C ../printf

minilibx:
	make -C ../minilibx-linux

# Regla de limpieza
clean:
	make -C ../printf/libft clean
	make -C ../printf clean
	rm -f $(OBJS)
	rm -rf $(OBJ_DIR)

# Regla para limpiar completamente
fclean: clean
	make -C ../printf/libft fclean
	make -C ../printf fclean
	rm -f $(NAME)

# Regla de reconstrucción completa
re: fclean all
