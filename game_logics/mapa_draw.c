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
#include "minilibx-linux"
#include "so_long.h"

void dibujo_mapa(t_mapa *data)
{
	int i;
	int j;

	i = 0;

	while(data->maps2[i])
	{
		j = 0;
		while(data->[i][j])
		{
			if(data->maps2[i][j] == '1')
				mlx_put_image_to_window(data->mlx, data->win,
				data->imagenes->wall, (*j) * 40, (*i) * 40);
			else if(data->maps2[i][j] == '0')
				mlx_put_image_to_window(data->mlx, data->win, 
				data->imagenes->space, (j*) * 40, (*i) * 40);
			else if(data->maps2[i][j] == 'P')
				mlx_put_image_to_window(data->mlx, data->win,
				data->imagenes->player, (*j) * 40, (*i ) * 40)
			else if(data->maps2[i][j] == 'C')
				mlx_put_image_to_window(data->mlx, data->win,
				data->imagenes->collect, j * 40, i * 40);
			else if(data->maps2[i][j] == 'E')
				mlx_put_image_to_window(data->mlx, data->win,
				data->imagenes->exit, j * 40, i * 40);
			j++;
		}
		i++;
	}
}
