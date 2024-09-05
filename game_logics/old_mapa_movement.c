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

void move_w(t_mapa *data)
{
    if (data->map[data->y - 1][data->x] != '1' && data->map[data->y - 1][data->x] != 'E')
    {
        if (data->map[data->y - 1][data->x] == 'C' || data->map[data->y - 1][data->x] == '0')
        {
            if (data->map[data->y - 1][data->x] == 'C')
                data->colectables--;
            data->map[data->y][data->x] = '0';
            data->map[data->y - 1][data->x] = 'P';
            data->y--;
            data->pasos++;
            write_itoa(data->pasos);
           // Alternar entre frames
            data->frame_count = (data->frame_count + 1) % 3;
            if (data->frame_count == 0)
                mlx_put_image_to_window(data->mlx, data->win, data->imagenes->player_frame1, data->x * 40, data->y * 40);
            else if (data->frame_count == 1)
                mlx_put_image_to_window(data->mlx, data->win, data->imagenes->player_frame2, data->x * 40, data->y * 40);
            else
                mlx_put_image_to_window(data->mlx, data->win, data->imagenes->player_frame3, data->x * 40, data->y * 40);
        }
    }
    else if (data->map[data->y - 1][data->x] == 'E' && data->colectables == 0)
        data->finish = 1;
    actualizar_pantalla(data);
}


void move_s(t_mapa *data)
{
    if (data->map[data->y + 1][data->x] != '1' && data->map[data->y + 1][data->x] != 'E')
    {
        if (data->map[data->y + 1][data->x] == 'C' || data->map[data->y + 1][data->x] == '0')
        {
            if (data->map[data->y + 1][data->x] == 'C')
                data->colectables--;
            data->map[data->y][data->x] = '0';
            data->map[data->y + 1][data->x] = 'P';
            data->y++;
            data->pasos++;
            write_itoa(data->pasos);

			data->frame_count = (data->frame_count + 1) % 3;
			if(data->frame_count == 0)
				mlx_put_image_to_window(data->mlx, data->win, data->imagenes->player_frame1, data->x * 40, data->y * 40);
			else if(data->frame_count == 1)
				mlx_put_image_to_window(data->mlx, data->win, data->imagenes->player_frame2, data->x * 40, data->y * 40);
			else
				mlx_put_image_to_window(data->mlx, data->win, data->imagenes->player_frame3, data->x * 40, data->y * 40);
		}
	}    
    else if (data->map[data->y + 1][data->x] == 'E' && data->colectables == 0)
        data->finish = 1;
    actualizar_pantalla(data);
}

void move_d(t_mapa *data)
{
    if (data->map[data->y][data->x + 1] != '1' && data->map[data->y][data->x + 1] != 'E')
    {
        if (data->map[data->y][data->x + 1] == 'C' || data->map[data->y][data->x + 1] == '0')
        {
            if (data->map[data->y][data->x + 1] == 'C')
                data->colectables--;
            data->map[data->y][data->x] = '0';
            data->map[data->y][data->x + 1] = 'P';
            data->x++;
            data->pasos++;
            write_itoa(data->pasos);

			data->frame_count = (data->frame_count + 1) % 3;
			if(data->frame_count == 0)
            	mlx_put_image_to_window(data->mlx, data->win, data->imagenes->player_frame1, data->x * 40, data->y * 40);
			else if(data->frame_count == 1)
				mlx_put_image_to_window(data->mlx, data->win, data->imagenes->player_frame2, data->x * 40, data->y * 40);
			else
				mlx_put_image_to_window(data->mlx, data->win, data->imagenes->player_frame3, data->x * 40, data->y * 40);
        }
    }
    else if (data->map[data->y][data->x + 1] == 'E' && data->colectables == 0)
        data->finish = 1;
    actualizar_pantalla(data);
}

void move_a(t_mapa *data)
{
    if (data->map[data->y][data->x - 1] != '1' && data->map[data->y][data->x - 1] != 'E')
    {
        if (data->map[data->y][data->x - 1] == 'C' || data->map[data->y][data->x - 1] == '0')
        {
            if (data->map[data->y][data->x - 1] == 'C')
                data->colectables--;
            data->map[data->y][data->x] = '0';
            data->map[data->y][data->x - 1] = 'P';
            data->x--;
            data->pasos++;
            write_itoa(data->pasos);

			data->frame_count = (data->frame_count + 1) % 3;
            if(data->frame_count == 0)
				mlx_put_image_to_window(data->mlx, data->win, data->imagenes->player_frame1, data->x * 40, data->y * 40);
			else if(data->frame_count == 1)
				mlx_put_image_to_window(data->mlx, data->win, data->imagenes->player_frame2, data->x * 40, data->y * 40);
			else
				mlx_put_image_to_window(data->mlx, data->win, data->imagenes->player_frame3, data->x * 40, data->y * 40);
        }
    }
    else if (data->map[data->y][data->x - 1] == 'E' && data->colectables == 0)
        data->finish = 1;
    actualizar_pantalla(data);
}

int key_hook(int keycode, void *param)
{
	t_mapa *data;

	data = (t_mapa *)param;
	printf("Tecla presionada --> %d\n", keycode);
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
