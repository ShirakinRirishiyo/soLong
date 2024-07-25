/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapa_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dediaz-f <dediaz-f@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:59:46 by dediaz-f          #+#    #+#             */
/*   Updated: 2024/07/23 16:59:46 by dediaz-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


void malloc_fail(void)
{
	ft_printf("Error\n");
	exit(EXIT_FAILURE);
}

void read_map(t_mapa *data)
{
	char *line;
	int fd;
	int i;

	fd = open(data->map, O_RDONLY);
	if(fd == -1)
		return;
	data->maps2 = (char **)malloc(sizeof(char *) * data->height + 1);
	if(!data->maps2)
		malloc_fail();
	while(i < data->height)
	{
		line = get_next_line(fd);
		if(!line)
			malloc_fail();
		data->maps2[i] = ft_strdup(line);
		if(!data->maps2[i])
			malloc_fail();
		data->maps2[i][data->width] = '\0';
		i++;
		free(line);
	}
	data->maps2[i] = NULL;
	close(fd)
}

void mapa_size(t_mapa *data)
{
	char *line;
	int fd;
	
	fd = open(data->map, O_RDONLY);
	line = get_next_line(fd);
	if(!line)
	{
		ft_printf("Error\n");
		exit(EXIT_FAILURE);
	}
	data->width = strlen(line) - 1;
	data->height = 0;
	while(line)
	{
		if((int)ft_strlen(line) - 1 != data->width)
			ft_printf("Error/Mapa invalido\n");
			exit(EXIT_FAILURE);
			data->heigth++;
			free(line)
			line = get_next_line(fd);

	}
	line = NULL;
	close(fd);
}