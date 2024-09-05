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


// Función para manejar fallos de memoria
void malloc_fail(void) {
    perror("Memory allocation error"); // <<<-- recordar leaks aquiii!!
    exit(EXIT_FAILURE);
}

// Función para calcular el tamaño del mapa
void mapa_size(t_mapa *data) {
    char *line;
    int fd;

    fd = open(data->text, O_RDONLY);
    if (fd == -1) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    data->width = 0;
    data->height = 0;

    while ((line = get_next_line(fd)) != NULL) {
        // Eliminar el carácter de nueva línea si existe
        int line_length = strlen(line);
        if (line[line_length - 1] == '\n') {
            line[line_length - 1] = '\0';
            line_length--;
        }

        if (data->height == 0) {
            data->width = line_length;  // Establecer el ancho basado en la primera línea
        } else if (line_length != data->width) {
            fprintf(stderr, "Error\nMap not valid at line %d\n", data->height + 1);
            free(line);
            close(fd);
            exit(EXIT_FAILURE);
        }

        data->height++;
        free(line);
    }

    if (data->height == 0) {
        fprintf(stderr, "Error\nEmpty map\n");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("Map width: %d\n", data->width);
    printf("Map height: %d\n", data->height);

    close(fd);
}

// Función para leer el mapa
void read_map(t_mapa *data) {
    char *line;
    int fd;
    int i;

    fd = open(data->text, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    data->map = (char **)malloc(sizeof(char *) * (data->height + 1));
    if (!data->map) {
        malloc_fail();
    }

    i = 0;
    while (i < data->height) {
        line = get_next_line(fd);
        if (!line) {
            perror("Error reading file");
            close(fd);
            exit(EXIT_FAILURE);
        }

        int line_length = ft_strlen(line);
        if (line[line_length - 1] == '\n') {
            line[line_length - 1] = '\0';
            line_length--;
        }

        if (line_length != data->width) {
            fprintf(stderr, "Error\nMap row width mismatch at row %d\n", i + 1);
            free(line);
            close(fd);
            exit(EXIT_FAILURE);
        }

        data->map[i] = (char *)malloc(sizeof(char) * (data->width + 1));
        if (!data->map[i]) {
            malloc_fail();
        }

        ft_strlcpy(data->map[i], line, data->width + 1);
        data->map[i][data->width] = '\0';

        printf("Map row %d: %s\n", i, data->map[i]);

        free(line);
        i++;
    }
    data->map[i] = NULL;
    close(fd);
}