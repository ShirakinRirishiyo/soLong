/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dediaz-f <dediaz-f@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 11:55:45 by dediaz-f          #+#    #+#             */
/*   Updated: 2024/07/13 11:55:45 by dediaz-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
#include "../printf/libft/libft.h"
#include "../printf/ft_printf.h"
#include "../minilibx-linux/mlx.h"


# define ESC	53
# define W		13
# define A		0
# define S		1
# define D		2
# define SPRITE_SIZE 40
# define BACKGROUND_COLOR 0x00FF00 // Verde puro en formato hexadecimal


// Definir rutas para las imágenes
# define WALL_IMAGE "../sprites/house.xpm"
# define SPACE_IMAGE "../sprites/cesped.xpm"
# define PLAYER_F1 "../sprites/player_frame1.xpm"
# define PLAYER_F2 "../sprites/player_frame2.xpm"
# define PLAYER_F3 "../sprites/player_frame3.xpm"
# define COLLECT1_IMAGE "../sprites/oritoabajo.xpm"
# define COLLECT2_IMAGE "../sprites/oritoarriba.xpm"
# define EXIT_IMAGE "../sprites/castle_purple.xpm"
# define FIRE1_IMAGE "../sprites/fuegoabajo.xpm"
# define FIRE2_IMAGE "../sprites/fuegoarriba.xpm"

# define VALIDOS "10CPE"


typedef struct s_check
{
	int **maps; //matriz para saber las posiciones en el map
	int coins_left; //moendas para colectar
} t_check;

typedef struct s_imagenes {
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


typedef struct s_mapa {
    char *text;     // Contenido completo del mapa en una sola cadena
    char **map;   // Contenido del mapa dividido en líneas (matriz de caracteres)
    int height;  //linea vertical para recorrer matriz
    int width;   //linea horizontal para recorrer matriz
    int x; //para actualizar la posicion del jugador
    int y; // para actualzar la posicion del jugador
    int player;  //jugador
    int current_frame;
    int total_frames;
    int frame_count;
    int animacion_fuego;
    void *background_img;
    int colectables; //cositas para comer
    int end;  //una sola salida
    void *mlx;//para iniciar la biblioteca
    void *win;//para la ventana (representa la ventana)
    unsigned int pasos; //pasos del jugador
	int finish; //autoriza practicamente el final del juego
    t_imagenes *imagenes;
} t_mapa;      


int write_itoa(int n);
int cargar_imagen(t_mapa *data, void **img,  char *ruta);
void fill_malloc(t_check *c, t_mapa *data);
void iter_check(t_check *c, t_mapa *data, int j, int i);
void ft_free(t_check *c, int height);
void posiciones_en_el_mapa(t_mapa *data);
void es_posible(t_mapa *data, int j, int i, int element);
void move_w(t_mapa *data);
void move_s(t_mapa *data);
void move_d(t_mapa *data);
void move_a(t_mapa *data);
void    reset_data(t_mapa *data, char *name);
int	frame_s(t_mapa *data);
int key_hook(int keycode, t_mapa *data);
void ft_printear(unsigned int n);
int exit_game(t_mapa *data);
void	ft_game_result(t_mapa *data);
void actualizar_pantalla(t_mapa *data);
void actualizar_animacion_fuego(t_mapa *data);
void dibujo_mapa(t_mapa *data);
void malloc_fail(void);
void read_map(t_mapa *data);
void mapa_size(t_mapa *data);
void objetos_de_mapa(t_mapa *data);
void caracter_valido(t_mapa *data);
void comprobacion_open_ber(t_mapa *data);
int check_rectangular(t_mapa *mapa);
int verificar_linea(t_mapa *data);
void check_general(t_mapa *data);
int es_pared_bordeadora(t_mapa *data, int i, int j);
void draw_grid(t_mapa *data); 
void reset_data(t_mapa *data, char *name);
void mapa_size(t_mapa *data);
void read_map(t_mapa *data);
void check_general(t_mapa *data);

#endif
