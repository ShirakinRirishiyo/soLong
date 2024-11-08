/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapa_movement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dediaz-f <dediaz-f@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:56:31 by dediaz-f          #+#    #+#             */
/*   Updated: 2024/07/29 13:56:31 by dediaz-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


void movement(t_mapa *data, int move_x, int move_y)
{
    // Mostrar la posición antes del movimiento
    printf("Posición actual: (%d, %d). Colectables restantes: %d\n", data->x, data->y, data->colectables);

    // Comprobar si hay una pared
    if (data->map[data->y + move_y][data->x + move_x] == '1') {
        printf("Movimiento bloqueado por una pared en (%d, %d)\n", data->y + move_y, data->x + move_x);  // Depuración
        return;
    }

    // Comprobar si el movimiento es hacia un colectable o una casilla vacía
    if (data->map[data->y + move_y][data->x + move_x] == 'C' || data->map[data->y + move_y][data->x + move_x] == '0') {
        if (data->map[data->y + move_y][data->x + move_x] == 'C') {
            data->colectables--;
            printf("Colectable recogido. Colectables restantes: %d\n", data->colectables);  // Depuración
        }
        // Actualizar el mapa
        data->map[data->y][data->x] = '0';
        data->map[data->y + move_y][data->x + move_x] = 'P';
        data->y += move_y;
        data->x += move_x;
        data->pasos++;

        // Imprimir el conteo de pasos
        printf("Movido a (%d, %d). Pasos: %d\n", data->x, data->y, data->pasos);  // Depuración
    }
    // Comprobar si es la salida
    else if (data->map[data->y + move_y][data->x + move_x] == 'E' && data->colectables == 0) {
        printf("¡Salida alcanzada! Colectables restantes: %d\n", data->colectables);  // Depuración
        exit_game(data);
    }
    // Actualizar pantalla
    actualizar_pantalla(data);
}



int key_hook(int keycode, void *param)
{
    t_mapa *data;

    data = (t_mapa *)param;

    // Depuración para ver qué tecla se ha presionado
    printf("Tecla presionada: %d\n", keycode);  // Depuración

    if (keycode == ESC)
        exit_game(data); // Salir del juego
    else if (keycode == W) {
        printf("Moviendo hacia arriba\n");  // Depuración
        movement(data, 0, -1); // Mover hacia arriba
    }
    else if (keycode == A) {
        printf("Moviendo hacia la izquierda\n");  // Depuración
        movement(data, -1, 0); // Mover hacia la izquierda
    }
    else if (keycode == S) {
        printf("Moviendo hacia abajo\n");  // Depuración
        movement(data, 0, 1); // Mover hacia abajo
    }
    else if (keycode == D) {
        printf("Moviendo hacia la derecha\n");  // Depuración
        movement(data, 1, 0); // Mover hacia la derecha
    }

    return (0);
}

