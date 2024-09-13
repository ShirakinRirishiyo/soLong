/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dediaz-f <dediaz-f@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:20:59 by dediaz-f          #+#    #+#             */
/*   Updated: 2024/09/11 16:11:22 by dediaz-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

typedef struct s_indices
{
    int i;
    int j;
    int end;
} t_indices;

void objetos_de_mapa(t_mapa *data)
{
    t_indices indices = {0, 0, 0};  // Inicializar todos los enteros a 0

    while (data->map[++indices.j])
    {
        indices.i = 0;
        while (data->map[indices.j][++indices.i])
        {
            if (data->map[indices.j][indices.i] == 'P')
            {
                data->x = indices.i;
                data->y = indices.j;
                data->player++;
            }
            else if (data->map[indices.j][indices.i] == 'C')
                data->colectables++;
            else if (data->map[indices.j][indices.i] == 'E')
                indices.end++;
        }
    }
    if (data->player != 1 || data->colectables < 1 || indices.end != 1)
    {
        ft_printf("Error\n");
        exit(EXIT_FAILURE);
    }
}


void caracter_valido(t_mapa *data)
{
    int i;
    int j;

    j = 0;
    while (data->map[j])
    {
		i = 0;
		while (data->map[j][i])
		{
			if (data->map[j][i] != '1' && data->map[j][i] != '0'
				&& data->map[j][i] != 'C' && data->map[j][i] != 'P'
				&& data->map[j][i] != 'E')
			{
				write(2, "Error\nBad map inputs\n", 21);
				exit (EXIT_FAILURE);
			}
			else
			i++;
		}
		j++;
	}
}

void comprobacion_open_ber(t_mapa *data) 
{
    size_t longitud;

    longitud = ft_strlen(data->text);
    if (longitud < 4 || ft_strncmp(&data->text[longitud - 4], ".ber", 4) != 0) {
        ft_printf("Error: el archivo debe tener la extensión .ber\n");
        exit(EXIT_FAILURE); // Salir del programa si la extensión es incorrecta
    }
    ft_printf("El archivo %s es válido\n", data->text);
}


int check_rectangular(t_mapa *mapa) 
{
    char *line;
    int first_line_length = -1;
    int is_rectangular = 1;
    
    int fd = open(mapa->text, O_RDONLY);
    if (fd == -1) 
    {
        ft_printf("Error opening file\n");
        exit(EXIT_FAILURE);
    }
    while ((line = get_next_line(fd)) != NULL) 
    {
        int current_line_length = ft_strlen(line);
        if (line[current_line_length - 1] == '\n') 
            current_line_length--;
        if (first_line_length == -1) 
        {
            first_line_length = current_line_length;
        } 
        else if (current_line_length != first_line_length)
            is_rectangular = 0;
        free(line);
    }
    if (close(fd) == -1) 
    {
        perror("Error closing file");
        return (-1);
    }
    return is_rectangular;
}

void verificar_linea(t_mapa *data)
{
    int i;
    int error;

    i = 0;
    error = 0;
	while (i < data->width)
	{
		if (data->map[0][i] != '1' || data->map[data->height - 1][i] != '1')
			error = 1;
		i++;
	}
	while (i < data->height)
	{
		if (data->map[i][0] != '1' || data->map[i][data->width - 1] != '1')
			error = 1;
		i++;
	}
	if (error != 0)
	{
		ft_printf("Error\nMap outline bad\n");
		exit (EXIT_FAILURE);
	}
}
