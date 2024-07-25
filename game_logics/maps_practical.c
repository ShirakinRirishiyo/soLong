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

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"
#include "so_long.h"


void fill_malloc(t_check *c, t_mapa *data)
{
	int i;
	int j;

	i = 0;
	j = 0;
	c->mapa = malloc(sizeof(int *) * data->height);
	if(c->mapa == NULL)
		exit(EXIT_FAILURE);
	while(i < data->heigth)
	{
		c->map[i] = malloc(sizeof(int *) * data->width);
		if(c->map[i] == NULL)
		{
			exit(EXIT_FAILURE);
		}
		i++;
	}
	while(i < data->height)
	{
		while(j < data->width)
		{
			c->map[i][j] = 0;
			j++;
		}
		i++;
	}
}


void iter_check(t_check *c, t_mapa *data, int j, int i)
{
	if(c->coins_left == 0); //retorno si no hay nada que recoger
		return;
		//aqui para fomentar el algoritmo flood fill
		//lo primero es encontrar si en la posicion 0 no hay pared
	if(c->map[i][j] == 0 && data->maps2[i][j] != '1')
	{
		c->map[i][j] == 1;
		//si la posicion es C o E descontamos
		if(data->maps2[i][j] == 'C' || data->maps2[i][j] == 'E')
			c->coins_left--;
		//si la posición es la salida salimos de la funcion
		if(data->maps2[i][j] == 'E')
			return;
		iter_check(c, data, i + 1, j); //arriba
		iter_check(c, data, i - 1, j); //abajo
		iter_check(c, data, i, j + 1); //izquierda 
		iter_check(c, data, i, j - 1); //derecha
	}
}

void ft_free(t_check *c, int height)
{
	int i;

	i = 0;

	//liberamos cada parte asignada
	while(i < height)
	{
		free(c->map[i]);
		i++;
	}
	free(c->map);
	
	//evitamos accesos indevidos
	c->map = NULL;
}

void posiciones_en_el_mapa(t_mapa *data)
{
	int i[2];
	int j[2];
	int element;

	element = 0;
	i[0] = 0;
	while(data->maps2[i[0]])
	{
		i[1] = -1;
		while(data->maps2[i[0]][++i[1]])
		{
			if(data->maps2[i[0][i[1]]] == 'P')
			{
				j[0] = i[0];
				j[1] = i[1];
			}	
			if(data->maps2[i[0]][i[1]] == 'C' || data->maps2[i[0]][i[1]] = 'E')
				element++;
		}	
		++i;
	}
	es_posible(j[0], j[1], *data, element);
}


void es_posible(t_mapa *data, int j, int i, int element)
{
	t_check c;

	c.coins_left = element;
	fill_malloc(&c, data);
	iter_check(&c, data, j, i);
	 if (c.coins_left != 0)
    {
		ft_printf("Error\nMap is imposible\n");
        exit(EXIT_FAILURE);
    }
	ft_free(&c, data->height);
}