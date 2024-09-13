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
    if (data->map[data->y + move_y][data->x + move_x] == '1')
		return ;
	if (data->map[data->y + move_y][data->x + move_x] == 'C' || data->map[data->y + move_y][data->x + move_x] == '0')
	{
		if (data->map[data->y + move_y][data->x + move_x] == 'C')
			data->colectables--;
		data->map[data->y][data->x] = '0';
		data->map[data->y + move_y][data->x + move_x] = 'P';
		data->y += move_y;
		data->x += move_x;
		data->pasos++;
		printf("Conteo de pasos: %d\n", data->pasos);
	}
    else if (data->map[data->y + move_y][data->x + move_x] == 'E' && data->colectables == 0)
		exit_game(data);
        // data->finish = 1;
    actualizar_pantalla(data);
}

int key_hook(int keycode, void *param)
{
	t_mapa *data;

	data = (t_mapa *)param;
	// printf("Tecla presionada --> %d\n", keycode);
    if (keycode == ESC)
        exit_game(data); // Salir del programa y liberar recursos
    else if (keycode == W)
        movement(data, 0, -1); // Mover hacia arriba
    else if (keycode == A)
        movement(data, -1, 0); // Mover hacia arriba
        // move_a(data); // Mover hacia la izquierda
    else if (keycode == S)
        movement(data, 0, 1); // Mover hacia arriba
        // move_s(data); // Mover hacia abajo
    else if (keycode == D)
        movement(data, 1, 0); // Mover hacia arriba
        // move_d(data); // Mover hacia la derecha
    return (0);
}
