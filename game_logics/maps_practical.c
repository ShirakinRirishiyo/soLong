/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps_practical.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dediaz-f <dediaz-f@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 20:51:07 by dediaz-f          #+#    #+#             */
/*   Updated: 2024/07/17 20:51:07 by dediaz-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void fill_malloc(t_check *c, t_mapa *data)
{
    int i, j;

    c->maps = malloc(sizeof(int *) * data->height);
    if (c->maps == NULL)
        exit(EXIT_FAILURE);
    for (i = 0; i < data->height; i++)
    {
        c->maps[i] = malloc(sizeof(int) * data->width); // Corregido a sizeof(int)
        if (c->maps[i] == NULL)
            exit(EXIT_FAILURE);
        for (j = 0; j < data->width; j++)
        {
            c->maps[i][j] = 0;
        }
    }
}

void iter_check(t_check *c, t_mapa *data, int i, int j)
{
    if (c->coins_left == 0) // retorno si no hay nada que recoger
        return;

    // Verificar que estamos dentro de los límites del mapa
    if (i < 0 || i >= data->height || j < 0 || j >= data->width)
        return;

    // Verificar si la posición actual es una pared o ya fue visitada
    if (data->map[i][j] == '1' || c->maps[i][j] == 1)
        return;

    // Marcar la posición actual como visitada
    c->maps[i][j] = 1;

    // Si la posición es una moneda o la salida, descontar
    if (data->map[i][j] == 'C' || data->map[i][j] == 'E')
        c->coins_left--;
    // Si la posición es la salida, salir de la función
    if (data->map[i][j] == 'E')
        return;
    // Llamar recursivamente en las cuatro direcciones
    iter_check(c, data, i + 1, j); // abajo
    iter_check(c, data, i - 1, j); // arriba
    iter_check(c, data, i, j + 1); // derecha
    iter_check(c, data, i, j - 1); // izquierda
}

void ft_free(t_check *c, int height)
{
    for (int i = 0; i < height; i++)
    {
        free(c->maps[i]);
    }
    free(c->maps);
    c->maps = NULL; // evitar accesos indebidos
}

void posiciones_en_el_mapa(t_mapa *data)
{
    int i, j;
    int element = 0;

    int start_i = -1, start_j = -1; // inicializamos los valores del jugador

    for (i = 0; i < data->height; i++)
    {
        for (j = 0; j < data->width; j++)
        {
            if (data->map[i][j] == 'P')
            {
                start_i = i;
                start_j = j;
            }
            if (data->map[i][j] == 'C' || data->map[i][j] == 'E')
                element++;
        }
    }
    es_posible(data, start_i, start_j, element);
}

void es_posible(t_mapa *data, int i, int j, int element)
{
    t_check c;

    c.coins_left = element;
    fill_malloc(&c, data);
    iter_check(&c, data, i, j);
    if (c.coins_left != 0)
    {
        ft_printf("Error\nMap is impossible\n");
        exit(EXIT_FAILURE);
    }
    ft_free(&c, data->height);
}