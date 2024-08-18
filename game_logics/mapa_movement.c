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
            write_itoa(data->pasos); // Escribe el número de pasos en la interfaz del juego
            mlx_put_image_to_window(data->mlx, data->win, data->imagenes->player_up, data->x * 40, data->y * 40);
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
            mlx_put_image_to_window(data->mlx, data->win, data->imagenes->player_down, data->x * 40, data->y * 40);
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
            mlx_put_image_to_window(data->mlx, data->win, data->imagenes->player_right, data->x * 40, data->y * 40);
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
            mlx_put_image_to_window(data->mlx, data->win, data->imagenes->player_left, data->x * 40, data->y * 40);
        }
    }
    else if (data->map[data->y][data->x - 1] == 'E' && data->colectables == 0)
        data->finish = 1;
    actualizar_pantalla(data);
}

int key_hook(int keycode, t_mapa *data)
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
