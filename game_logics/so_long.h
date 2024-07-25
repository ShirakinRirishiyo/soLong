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
#include "../minilibx/mlx_init.c"

typedef struct s_check
{
	int **map; //matriz para saber las posiciones en el map
	int coins_left; //moendas para colectar
} t_check;

typedef struct s_imagenes
{
    void *space;
    void *exit;
    void *wall;
    void *player;
    void *winner;
}   t_imagenes;



typedef struct s_mapa {
    char *filename; // Nombre del archivo del mapa
    char *map;     // Contenido completo del mapa en una sola cadena
    char **maps2;   // Contenido del mapa dividido en líneas (matriz de caracteres)
    int height;  //linea vertical para recorrer matriz
    int width;   //linea horizontal para recorrer matriz
    int x; //para actualizar la posicion del jugador
    int y; // para actualzar la posicion del jugador
    int player;  //jugador
    int colectables; //cositas para comer
    int end;  //una sola salida
    void *mlx;//para iniciar la biblioteca
    void *win;//para la ventana (representa la ventana)
    unsigned int pasos; //pasos del jugador
	int finish; //autoriza practicamente el final del juego
} t_mapa;

#endif