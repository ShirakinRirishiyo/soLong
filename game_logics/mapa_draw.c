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

void dibujo_mapa(t_mapa *data) {
    int i;
    int j;

    // Verificar que los datos estén correctamente inicializados
    if (data == NULL || data->map == NULL || data->imagenes == NULL) {
        printf("Error: Datos no inicializados.\n");
        return;
    }
    printf("Dibujando el mapa...\n");
    // Iterar sobre cada fila del mapa
    i = 0;
    while (data->map[i]) 
    {
        j = 0;
        while (data->map[i][j]) 
        {
            // Debug: Imprimir coordenadas y contenido del mapa
            printf("Dibujando en (%d, %d): %c\n", i, j, data->map[i][j]);
            // Dibujar diferentes elementos del mapa
            if (data->map[i][j] == '1') {
                if (es_pared_bordeadora(data, j, i)) {
                    printf("Dibujando pared bordeadora en (%d, %d)\n", i, j);
                    if (mlx_put_image_to_window(data->mlx, data->win,
                        data->imagenes->wall, j * 40, i * 40) != 0) {
                        printf("Error al dibujar pared bordeadora en (%d, %d)\n", i, j);
                    }
                } else {
                    if (data->animacion_fuego) {
                        printf("Dibujando fuego1 en (%d, %d)\n", i, j);
                        if (mlx_put_image_to_window(data->mlx, data->win,
                            data->imagenes->fuego1, j * 40, i * 40) != 0) {
                            printf("Error al dibujar fuego1 en (%d, %d)\n", i, j);
                        }
                    } else {
                        printf("Dibujando fuego2 en (%d, %d)\n", i, j);
                        if (mlx_put_image_to_window(data->mlx, data->win,
                            data->imagenes->fuego2, j * 40, i * 40) != 0) {
                            printf("Error al dibujar fuego2 en (%d, %d)\n", i, j);
                        }
                    }
                }
            } else if (data->map[i][j] == '0') {
                printf("Dibujando espacio en (%d, %d)\n", i, j);
                if (mlx_put_image_to_window(data->mlx, data->win,
                    data->imagenes->space, j * 40, i * 40) != 0) {
                    printf("Error al dibujar espacio en (%d, %d)\n", i, j);
                }
            } else if (data->map[i][j] == 'P') {
                printf("Dibujando jugador en (%d, %d)\n", i, j);
                if (mlx_put_image_to_window(data->mlx, data->win,
                    data->imagenes->player_down, j * 40, i * 40) != 0) {
                    printf("Error al dibujar jugador en (%d, %d)\n", i, j);
                }
            } else if (data->map[i][j] == 'C') {
                printf("Dibujando colectable en (%d, %d)\n", i, j);
                if (mlx_put_image_to_window(data->mlx, data->win,
                    data->imagenes->collect, j * 40, i * 40) != 0) {
                    printf("Error al dibujar colectable en (%d, %d)\n", i, j);
                }
            } else if (data->map[i][j] == 'E') {
                printf("Dibujando salida en (%d, %d)\n", i, j);
                if (mlx_put_image_to_window(data->mlx, data->win,
                    data->imagenes->exit, j * 40, i * 40) != 0) {
                    printf("Error al dibujar salida en (%d, %d)\n", i, j);
                }
            } else {
                printf("Error: Carácter no válido '%c' en (%d, %d)\n", data->map[i][j], i, j);
            }
            j++;
        }
        i++;
    }
    printf("Mapa dibujado correctamente.\n");
}
