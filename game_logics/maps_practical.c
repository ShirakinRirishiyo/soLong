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

void	fill_malloc(t_check *c, t_mapa *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	c->maps = malloc(sizeof(int *) * data->height);
	if (c->maps == NULL)
		exit(EXIT_FAILURE);
	while (i < data->height)
	{
		c->maps[i] = malloc(sizeof(int) * data->width);
		if (c->maps[i] == NULL)
			exit(EXIT_FAILURE);
		while (j < data->width)
		{
			c->maps[i][j] = 0;
			j++;
		}
		i++;
	}
}

void	iter_check(t_check *c, t_mapa *data, int i, int j)
{
	if (c->coins_left == 0)
		return ;
	if (i < 0 || i >= data->height || j < 0 || j >= data->width)
		return ;
	if (data->map[i][j] == '1' || c->maps[i][j] == 1)
		return ;
	c->maps[i][j] = 1;
	if (data->map[i][j] == 'C' || data->map[i][j] == 'E')
		c->coins_left--;
	if (data->map[i][j] == 'E')
		return ;
	iter_check(c, data, i + 1, j);
	iter_check(c, data, i - 1, j);
	iter_check(c, data, i, j + 1);
	iter_check(c, data, i, j - 1);
}

void	ft_free(t_check *c, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(c->maps[i]);
		i++;
	}
	free(c->maps);
	c->maps = NULL;
}

void	posiciones_en_el_mapa(t_mapa *data)
{
	t_place_mapa	place;

	place.i = 0;
	place.j = 0;
	place.element = 0;
	place.start_i = -1;
	place.start_j = -1;
	while (place.i < data->height)
	{
		while (place.j < data->width)
		{
			if (data->map[place.i][place.j] == 'P')
			{
				place.start_i = place.i;
				place.start_j = place.j;
			}
			if (data->map[place.i][place.j] == 'C'
					|| data->map[place.i][place.j] == 'E')
				place.element++;
			place.j++;
		}
		place.i++;
		place.j = 0;
	}
	es_posible(data, place.start_i, place.start_j, place.element);
}

void	es_posible(t_mapa *data, int i, int j, int element)
{
	t_check	c;

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
