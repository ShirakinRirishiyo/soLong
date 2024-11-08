/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dediaz-f <dediaz-f@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:48:48 by dediaz-f          #+#    #+#             */
/*   Updated: 2024/11/08 09:46:58 by dediaz-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_printear(unsigned int n)
{
	char *str;

	str = ft_itoa(n);
	if (str)
	{
		ft_printf("Número de pasos: %s\n", str);
		free(str);
	}
	else
	{
		ft_printf("Error al convertir el número de pasos.\n");
	}
}

int exit_game(t_mapa *data)
{
    printf("¡Felicidades! Has completado el juego.\n");
    printf("Colectables restantes: %d\n", data->colectables);  // Depuración// Función de salida (cerrar ventana, etc.)
    mlx_destroy_window(data->mlx, data->win);  // Destruir la ventana
    free(data->imagenes);  // Liberar las imágenes si se asignaron dinámicamente
    free(data);  // Liberar la estructura de datos
    exit(EXIT_FAILURE);
}

void manejar_error(const char *mensaje) 
{
    fprintf(stderr, "%s\n", mensaje);
    exit(EXIT_FAILURE);  // Finaliza el programa con un error
}

void	ft_game_result(t_mapa *data)
{
	int	x;
	int	y;
	mlx_clear_window(data->mlx, data->win);
	x = data->width * 40 / 2.4;
	y = data->height * 40 / 4;
	ft_printf("Dibujando resultado en (%d, %d)\n", x, y);
	mlx_put_image_to_window(data->mlx,
			data->win, data->imagenes->player_frame1, x, y);
}

void	actualizar_pantalla(t_mapa *data)
{
	mlx_clear_window(data->mlx, data->win);
	dibujo_mapa(data);
}
