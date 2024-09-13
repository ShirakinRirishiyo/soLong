/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapa_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dediaz-f <dediaz-f@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:56:09 by dediaz-f          #+#    #+#             */
/*   Updated: 2024/07/22 12:56:09 by dediaz-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "so_long.h"

int es_pared_bordeadora(t_mapa *data, int j, int i) {
    // Comprobar si la posición está en el borde del mapa
    if (i == 0 || i == data->height - 1 || j == 0 || j == data->width - 1) {
        return 1;  // Verdadero: es una pared bordeadora
    }
    return 0;  // Falso: no es una pared bordeadora
}


void dibujar_elemento(t_mapa *data, void *img, int x, int y) {
    if (mlx_put_image_to_window(mlx, win, img, x * SPRITE_SIZE, y * SPRITE_SIZE) != 0) {
        printf("Error al dibujar en (%d, %d)\n", y, x);
    }
}


void dibujar_elemento_del_mapa(t_mapa *data, int i, int j) {
    switch (data->map[i][j]) {
        case '1':
            // if (es_pared_bordeadora(data, j, i))  //por mientras comentamos esto  < nwn >
			dibujar_elemento(data->mlx, data->win, data->imagenes->wall, j, i);
            // } else {
            //     dibujar_elemento(data->mlx, data->win, data->imagenes->fuego1, j, i);
            break;
        case '0':
            dibujar_elemento(data->mlx, data->win, data->imagenes->space, j, i);
            break;
        case 'P':
            {
                // void *player_frames[] = {
                //     data->imagenes->player_frame1,  // Frame 0
                //     data->imagenes->player_frame2,// Frame 1
                //     data->imagenes->player_frame3 // Frame 2
                // };
                dibujar_elemento(data->mlx, data->win, data->imagenes->player_frame1, j, i);
            }
            break;
        case 'C':
            dibujar_elemento(data->mlx, data->win, data->imagenes->collect, j, i);
            break;
        case 'E':
            dibujar_elemento(data->mlx, data->win, data->imagenes->exit, j, i);
            break;
        default:
            printf(RED"Error: Carácter no válido '%c' en (%d, %d)\n"RESET, data->map[i][j], i, j);
	}
}


void dibujo_mapa(t_mapa *data) {
    int i = 0;
    int j;
    // static int anim_frame = 0;
	printf(GREEN"Coordenadas --> (%d, %d)\n"RESET, data->x, data->y);
    if (data == NULL || data->map == NULL || data->imagenes == NULL) {
        printf("Error: Datos no inicializados.\n");
        return;
    }

    // anim_frame = (anim_frame + 1) % 3; // Cambiar frame

    printf("Dibujando el mapa...\n");
    while (data->map[i]) {  // Iterar sobre cada fila del mapa
        j = 0;
        while (data->map[i][j]) {  // Iterar sobre cada columna en la fila
            dibujar_elemento_del_mapa(data, i, j);  // Llamar a la nueva función para cada celda
            j++;
        }
        i++;
    }
    printf("Mapa dibujado correctamente.\n");
}
