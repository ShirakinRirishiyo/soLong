/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_maps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dediaz-f <dediaz-f@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:49:45 by dediaz-f          #+#    #+#             */
/*   Updated: 2024/11/07 20:54:06 by dediaz-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void init_map(t_mapa *data, t_mapa_info *info)
{
    info->fd = open(data->text, O_RDONLY);  // Abre el archivo de texto del mapa
    if (info->fd == -1)
        manejar_error_fd("Error al abrir el archivo de mapa.\n", -1, NULL);  // Error al abrir el archivo

    data->map = (char **)malloc(sizeof(char *) * (data->height + 1));  // Reserva espacio para el mapa
    if (!data->map)
        malloc_fail();  // Llama a una función que maneja el fallo de malloc

    info->i = 0;  // Inicializa el índice de la línea
}

void procesa_line(t_mapa *data, t_mapa_info *info)
{
    info->line_length = ft_strlen(info->line);  // Obtiene la longitud de la línea
    if (info->line[info->line_length - 1] == '\n')  // Si la línea termina en salto de línea
    {
        info->line[info->line_length - 1] = '\0';  // Elimina el salto de línea
        info->line_length--;  // Ajusta la longitud de la línea
    }

    if (info->line_length != data->width)  // Si la longitud de la línea no coincide con el ancho del mapa
    {
        free(info->line);  // Libera la memoria de la línea
        close(info->fd);  // Cierra el archivo
        manejar_error_fd("El archivo de mapa tiene líneas de longitud incorrecta.\n", info->fd, NULL);  // Llama a manejar_error_fd
    }
    data->map[info->i] = (char *)malloc(sizeof(char) * (data->width + 1));  // Reserva espacio para la línea en el mapa
    if (!data->map[info->i])
        malloc_fail();  // Llama a la función para manejar fallos de malloc

    ft_strlcpy(data->map[info->i], info->line, data->width + 1);  // Copia la línea al mapa
    // NO liberar info->line aquí
}