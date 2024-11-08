/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dediaz-f <dediaz-f@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 11:55:45 by dediaz-f          #+#    #+#             */
/*   Updated: 2024/11/07 12:32:46 by dediaz-f         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

# ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../printf/libft/libft.h"
# include "../printf/ft_printf.h"
# include "../minilibx-linux/mlx.h"


# define ESC	65307
# define W		119
# define A		97
# define S		115
# define D		100
# define SPRITE_SIZE 64
# define BACKGROUND_COLOR 0x00FF00 

# define RED "\033[0;31m"
# define BLUE "\033[0;34m"
# define YELLOW "\033[0;33m"
# define GREEN "\033[0;32m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;97m"
# define RESET "\033[0m"

# define WALL_IMAGE "../sprites/walls.xpm"
# define SPACE_IMAGE "../sprites/pared.xpm"
# define PLAYER_F1 "../sprites/player1.xpm"
# define PLAYER_F2 "../sprites/player2.xpm"
# define PLAYER_F3 "../sprites/player3.xpm"
# define COLLECT1_IMAGE "../sprites/oritoabajo.xpm"
# define COLLECT2_IMAGE "../sprites/oritoarriba.xpm"
# define EXIT_IMAGE "../sprites/castle.xpm"
# define FIRE1_IMAGE "../sprites/fuegoabajo.xpm"
# define FIRE2_IMAGE "../sprites/fuegoarriba.xpm"

# define VALIDOS "10CPE"

typedef struct s_check
{
	int **maps;
	int coins_left;
    int found_exit;
    int found_collectible;
} t_check;

typedef struct s_place_mapa
{
    int i;             
    int j;             
    int element;       
    int start_i;       
    int start_j;       
} t_place_mapa;

typedef struct s_imagenes
{
    void *wall;
    void *space;
    void *player_frame1;
    void *player_frame2;
    void *player_frame3;
    void *collect;
    void *collect2;
    void *exit;
    void *torre;
    void *fuego1;
    void *fuego2;
} t_imagenes;


typedef struct s_mapa
{
    char *text;    
    char **map;   
    int height;  
    int width;  
    int x; 
    int y; 
    int player;
    int current_frame;
    int total_frames;
    int player_frame;
    int frame_count;
    int animacion_fuego;
    void *background_img;
    int colectables; 
    int end; 
    void *mlx;
    void *win;
    unsigned int pasos; 
	int finish; 
    t_imagenes *imagenes;
} t_mapa;      

typedef struct s_indices 
{
    int i;   
    int j;   
    int end; 
} t_indices;

typedef struct s_contxt
{
    void    *mlx;        
    void    *win;        
    t_imagenes *imagenes; 
} t_contxt;

typedef struct s_mapa_info {
    int fd;                    // Descriptor de archivo para el archivo del mapa
    char *line;                // Línea de texto actual leída del archivo
    int line_length;           // Longitud de la línea
    int current_line_length;   // Longitud de la línea actual
    int first_line_length;     // Longitud de la primera línea
    int is_rectangular;        // Bandera para verificar si el mapa es rectangular
    int i;                     // Contador de líneas
} t_mapa_info;


int write_itoa(int n);
int cargar_imagen(t_mapa *data, void **img,  char *ruta);
void fill_malloc(t_check *c, t_mapa *data);
void iter_check(t_check *c, t_mapa *data, int j, int i);
void ft_free(t_check *c, int height);
void posiciones_en_el_mapa(t_mapa *data);
void manejar_error_fd(const char *mensaje, int fd, char *line);
void dibujar_mapa(t_mapa *data); 
void procesa_line(t_mapa *data, t_mapa_info *info);
void es_posible(t_mapa *data, int j, int i, int element);
void move_w(t_mapa *data);
void move_s(t_mapa *data);
void move_d(t_mapa *data);
void move_a(t_mapa *data);
void init_map(t_mapa *data, t_mapa_info *info);
void    reset_data(t_mapa *data, char *name);
int	frame_s(t_mapa *data);
// int key_hook(int keycode, t_mapa *data);
int key_hook(int keycode, void *param);
void ft_printear(unsigned int n);
int exit_game(t_mapa *data);
void	ft_game_result(t_mapa *data);
void	manejar_error(const char *mensaje);
void actualizar_pantalla(t_mapa *data);
void actualizar_animacion_fuego(t_mapa *data);
void dibujo_mapa(t_mapa *data);
void malloc_fail(void);
void read_map(t_mapa *data);
void mapa_size(t_mapa *data);
void objetos_de_mapa(t_mapa *data);
void caracter_valido(t_mapa *data);
int	cargar_imagenes(t_mapa *data);
void comprobacion_open_ber(t_mapa *data);
int check_rectangular(t_mapa *mapa);
void llamada_funciones(t_mapa *data, char **argv);
void verificar_linea(t_mapa *data);
void check_general(t_mapa *data);
int es_pared_bordeadora(t_mapa *data, int i, int j);
void draw_grid(t_mapa *data); 
void reset_data(t_mapa *data, char *name);
void check_general(t_mapa *data);

#endif