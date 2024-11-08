/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dediaz-f <dediaz-f@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:20:59 by dediaz-f          #+#    #+#             */
/*   Updated: 2024/11/08 09:51:31 by dediaz-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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


void	caracter_valido(t_mapa *data)
{
	int	i;
	int	j;

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

void	comprobacion_open_ber(t_mapa *data)
{
	size_t	longitud;

	longitud = ft_strlen(data->text);
	if (longitud < 4 || ft_strncmp(&data->text[longitud - 4], ".ber", 4) != 0)
	{
		ft_printf("Error: el archivo debe tener la extensión .ber\n");
		exit(EXIT_FAILURE);
	}
	ft_printf("El archivo %s es válido\n", data->text);
}

int	check_rectangular(t_mapa *mapa)
{
	t_mapa_info checker;

	// Abrir el archivo
	checker.fd = open(mapa->text, O_RDONLY);
	if (checker.fd == -1)
		manejar_error_fd("Error al abrir el archivo", checker.fd, NULL);

	// Inicialización de variables de longitud
	checker.first_line_length = -1;
	checker.is_rectangular = 1;// Leer cada línea del archivo
	checker.line = get_next_line(checker.fd);
	while (checker.line != NULL)
	{
		// Obtener la longitud de la línea actual
		checker.current_line_length = ft_strlen(checker.line);	
		// Verificar y eliminar el salto de línea, si existe
		if (checker.current_line_length > 0 && checker.line[checker.current_line_length - 1] == '\n')
			checker.current_line_length--;

		// Configurar la primera línea como referencia
		if (checker.first_line_length == -1)
			checker.first_line_length = checker.current_line_length;
		else if (checker.current_line_length != checker.first_line_length)
		{
			// Si la longitud no coincide, no es rectangular
			checker.is_rectangular = 0;
			free(checker.line);
			break;
		}
		free(checker.line);
		checker.line = get_next_line(checker.fd);
	}
	// Cerrar el archivo y verificar errores
	if (close(checker.fd) == -1)
		manejar_error("Error al leer el archivo");

	return (checker.is_rectangular);
}


void verificar_linea(t_mapa *data)
{
    int i;
    int error;

    i = 0;
    error = 0;
    printf("Verificando las paredes del mapa...\n");
    
    // Verificar paredes superior e inferior (borde horizontal)
    while (i < data->width)
    {
        // Imprimir el valor que estamos verificando en la pared superior e inferior
        printf("Comprobando pared superior en (0, %d): %c\n", i, data->map[0][i]);
        printf("Comprobando pared inferior en (%d, %d): %c\n", data->height - 1, i, data->map[data->height - 1][i]);

        // Si el valor no es 1 en el borde superior o inferior, marcar el error
        if (data->map[0][i] != '1' || data->map[data->height - 1][i] != '1')
        {
            error = 1;
            break;
        }
        i++;
    }

    i = 0; // Reset index for left/right verification
    // Verificar paredes izquierda y derecha (borde vertical)
    while (i < data->height)
    {
        // Imprimir el valor que estamos verificando en la pared izquierda y derecha
        printf("Comprobando pared izquierda en (%d, 0): %c\n", i, data->map[i][0]);
        printf("Comprobando pared derecha en (%d, %d): %c\n", i, data->width - 1, data->map[i][data->width - 1]);

        // Si el valor no es 1 en el borde izquierdo o derecho, marcar el error
        if (data->map[i][0] != '1' || data->map[i][data->width - 1] != '1')
        {
            error = 1;
            break;
        }
        i++;
    }

    if (error != 0)
    {
        printf("Error: Hay un error en las paredes del mapa.\n");
        manejar_error("Error\n");
    }
    else
    {
        printf("Las paredes del mapa están verificadas correctamente.\n");
    }
}