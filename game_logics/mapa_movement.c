/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapa_movement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dediaz-f <dediaz-f@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:03:20 by dediaz-f          #+#    #+#             */
/*   Updated: 2024/07/24 16:03:20 by dediaz-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


int key_hook(int keycode, t_info_map *data)
{
    if (keycode == ESC)
        exit_game(data); // Salir del programa y liberar recursos
    else if (keycode == W)
        move_w(data); // Mover hacia arriba
    else if (keycode == A)
        move_a(data); // Mover hacia la izquierda
    else if (keycode == S)
        move_s(data); // Mover hacia abajo
    else if (keycode == D)
        move_d(data); // Mover hacia la derecha
    return (0);
}


void move_w(t_mapa *data)
{
	if(data->maps2[data->y - 1][data-x] != '1' && data->maps2[data->y - 1][data-x] != E)
	{
		if(data->maps2[data->y - 1][data-x] == 'C' || (data->maps2[data->y - 1][data-x]) == '0')
		{
			if(data-maps[data->y - 1][data-x] == 'C')
				data->colectables--;
		} 
		data->maps2[data->y][data->x] = '0';
		data->maps2[data->y - 1][data->x] = 'P';
	}
	data->y--;
	data->pasos++;
	ft_write_itoa(data->step); // Escribe el número de pasos en la interfaz del juego
   	else if (data->map[data->y - 1][data->x] == 'E' && data->count == 0)
        data->finish = 1;
}

void move_s(t_mapa *data)
{
	if(data->maps2[data->y + 1][data->x] != '1' && data->maps2[data->y +1][data->x] != 'E')
	{
		if(data->maps2[data->y + 1][data->x] == 'C' || data->maps2[data->y +1][data->x] == '0')
		{
			if(data->maps2[data->y +1][data->x] == 'C')
				data->colectables--;
		}
		data->maps2[data->y][data->x] == '0';
		data->maps2[data->y + 1][data->x] == 'P';
	}
	data->y++;
	data->pasos++;
	ft_write_itoa(data->pasos);
	else if (data->maps2[data->y + 1][data->x] == 'E' && data->colectables == 0)
		data->finish = 1;
}

void move_d(t_mapa *data)
{
	i(data->maps2[data->y][data->x + 1] != '1' && data->maps2[data->y][data->x + 1] != 'E')
	{
		if(data->maps2[data->y][data->x + 1] == 'C' || data->maps2[data->y][data->x + 1] == '0')
		{
			if(data->maps2[data->y][data->x + 1] == 'C')
				data->colectables--;
		}
		data->maps2[data->y][data->x] == '0';
		data->maps2[data->y][data->x + 1] == 'P';
	}
	data->x++;
	data->pasos++;
	ft_write_itoa(data->pasos);
	else if (data->maps2[data->y][data->x + 1] == 'E' && data->colectables == 0)
		data->finish = 1;
}

void move_a(t_mapa *data)
{
	if (data->maps2[data->y][data->x - 1] != '1' && data->maps2[data->y][data->x - 1] != 'E')
	{
		if (data->maps2[data->y][data->x - 1] == 'C' || data->maps2[data->y][data->x - 1] == '0')
		{
			if (data->maps2[data->y][data->x -1] == 'C')
				data->colectables--;
		}
		data->maps2[data->y][data->x] == '0';
		data->maps2[data->y][data->x - 1] == 'P';
	}
	data->x--;
	data->pasos++;
	ft_write_pasos(data->pasos);
	else if (data->maps[data->y][data->x - 1] == 'E' && data->colectables == 0)
		data->finish = 1;
}
