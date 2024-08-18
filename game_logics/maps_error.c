/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dediaz-f <dediaz-f@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:20:59 by dediaz-f          #+#    #+#             */
/*   Updated: 2024/08/10 14:21:46 by dediaz-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


void	objetos_de_mapa(t_mapa *data)
{
	int	j;
	int	i;
	int	end;

	end = 0;
	j = 0;
	while (data->map[++j])
	{
		i = 0;
		while (data->map[j][++i])
		{
			if (data->map[j][i] == 'P')
				data->player++;
			if (data->map[j][i] == 'C')
				data->colectables++;
			if (data->map[j][i] == 'E')
				end++;
		}
	}
	if (data->player != 1 || data->colectables < 1 || end != 1)
	{
		write(2, "Error\nBad map inputs\n", 21);
		exit (EXIT_FAILURE);
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
        return -1;
    }
    return is_rectangular;
}

int verificar_linea(t_mapa *data)
{
    int i;

    // Verificar los bordes superior e inferior
    for (i = 0; i < data->width; i++)
    {
        if (data->map[0][i] != '1' || data->map[data->height - 1][i] != '1')
        {
            ft_printf("Error: Bordes horizontales deben ser '1' en posición (%d, %d)\n", (data->map[0][i] != '1') ? 0 : data->height - 1, i);
            return 0;
        }
    }

    // Verificar los bordes izquierdo y derecho
    for (i = 0; i < data->height; i++)
    {
        if (data->map[i][0] != '1' || data->map[i][data->width - 1] != '1')
        {
            ft_printf("Error: Bordes verticales deben ser '1' en posición (%d, %d)\n", i, (data->map[i][0] != '1') ? 0 : data->width - 1);
            return 0;
        }
    }
    
    return 1;
}
