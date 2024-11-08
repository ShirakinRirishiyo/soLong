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

void	malloc_fail(void)
{
	perror("Memory allocation error");
	exit(EXIT_FAILURE);
}

int open_file(const char *filename)
{
    int fd;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        manejar_error("Error al abrir el archivo");
        return -1; 
    }
    return fd;  
}

int get_line_length(char *line)
{
    int length;

    length = ft_strlen(line);
    if (length > 0 && line[length - 1] == '\n')
    {
        line[length - 1] = '\0';  // Eliminar el salto de línea
        length--;
    }
    return length;
}


void mapa_size(t_mapa *data)
{
    t_mapa_info info;

    info.fd = open_file(data->text);
    if (info.fd < 0)  
        manejar_error_fd("Error al abrir el archivo", info.fd, NULL);
    
    // Leer la primera línea para obtener el ancho
    info.line = get_next_line(info.fd);
    if (!info.line)
        manejar_error_fd("Error al leer la primera línea", info.fd, info.line);

    data->width = get_line_length(info.line);
    data->height = 1;  // Inicializa height en 1 para incluir la primera línea
    free(info.line);

    // Leer el resto de las líneas para determinar la altura del mapa
    while ((info.line = get_next_line(info.fd)) != NULL)
    {
        info.line_length = get_line_length(info.line);

        if (info.line_length != data->width)
            manejar_error_fd("Líneas con longitudes inconsistentes", info.fd, info.line);

        data->height++;  // Aumenta el contador de altura
        free(info.line);
    }

    if (data->height == 0)
        manejar_error_fd("El archivo está vacío", info.fd, NULL);

    close(info.fd); 
}

void read_map(t_mapa *data)
{
    t_mapa_info info;

    data->x = -1;  // Inicializa x en -1
    data->y = -1;  // Inicializa y en -1
    data->colectables = 0;  // Asegúrate de que la cuenta de coleccionables empiece en 0
    init_map(data, &info);  // Inicializa el mapa y la estructura `info`
    info.fd = open_file(data->text);

    // Recorremos el archivo línea por línea
    info.i = 0;
    while (info.i < data->height)  // Bucle que recorre cada fila
    {
        info.line = get_next_line(info.fd);
        if (!info.line)
            manejar_error_fd("Error al leer el mapa", info.fd, NULL);

        info.line_length = get_line_length(info.line);

        // Verifica si se ha encontrado la posición de 'P'
        if (data->x == -1 && data->y == -1)
        {
            char *pos_p = strchr(info.line, 'P');
            if (pos_p != NULL)
            {
                data->y = info.i;                // Fila donde se encontró 'P'
                data->x = pos_p - info.line;     // Columna donde se encontró 'P'
                printf("Posición inicial de P encontrada: (%d, %d)\n", data->y, data->x);
            }
        }

        // Procesamos cada celda en la línea
        int j = 0;
        while (j < info.line_length)  // Recorre cada columna de la fila
        {
            if (info.line[j] == 'C') {
                data->colectables++;  // Aumenta el contador de coleccionables
            }
            j++;
        }

        // Procesa la línea y la almacena en el mapa
        procesa_line(data, &info);

        // Incrementamos el índice de filas
        info.i++;
        free(info.line);  // Liberar la línea después de procesarla
    }
    data->map[info.i] = NULL;  // Marca el final del mapa
    close(info.fd);  // Cierra el archivo
}
