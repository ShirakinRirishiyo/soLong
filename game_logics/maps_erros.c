/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps_erros.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dediaz-f <dediaz-f@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:20:59 by dediaz-f          #+#    #+#             */
/*   Updated: 2024/07/26 09:15:24 by dediaz-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#define VALIDOS "10CPE"


void objetos_de_mapa(t_mapa *data)
{
    int i;
    int j;
    int end;

    end = 0;
    j = 0;
    while(data->maps2[j])
    {
        i = 0;  
        while(data->maps2[j][i])
        {
            if(data->maps2[j][i] == 'P')
                data->player++;
            if(data->maps2[j][i] == 'C')
                data->colectables++;
            if(data->maps2[j][i] == 'E')
                data->end++;
            i++;
        } 
        j++;    
    }
    if (data->end != 1 || data->colectables < 1 || data->player != 1)
            exit(EXIT_FAILURE);
}

void caracter_valido(t_mapa *data)
{
    int i;
    int j;

    j = 0;
    while (data->maps2[j])
    {
        i = 0;
        while (data->maps2[j][i] != '\0')
        {
            if (strchr(VALIDOS, data->maps2[j][i]) != NULL)
                i++;
            else
            {
               ft_printf("Error\nBad map inputs\n");
                exit(EXIT_FAILURE);
            }
        }
        j++;
    }
    return;
}

void comprobacion_open_ber(t_mapa *data) 
{
    int file;
    size_t longitud;

    file = open(data->filename, O_RDONLY);
    if (file == -1) {
        printf("El archivo no se puede abrir\n");
        exit(EXIT_FAILURE);
    }
    close(file);
    longitud = ft_strlen(data->filename);
    if (longitud < 4 || ft_strcmp(&data->filename[longitud - 4], ".ber") != 0) {
        ft_printf("Error: el archivo debe tener la extensión .ber\n");
        exit(EXIT_FAILURE); // Salir del programa si la extensión es incorrecta
    }
    ft_printf("El archivo %s es válido\n", data->filename);
}


int check_rectangular(t_mapa *mapa) 
{
    char *line;
    int first_line_length = -1;
    int is_rectangular = 1;
    
    int fd = open(mapa->filename, O_RDONLY);
    if (fd == -1) 
    {
        ft_printf("Error opening file\n");
        exit(EXIT_FAILURE);
    }
    while ((line = get_next_line(fd)) != NULL) 
    {
        int current_line_length = strlen(line);
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

    i = 0;
    while(i < data->width)
    {
        if(data->maps2[0][i] != '1' || data->maps2[data->width - 1][i] != '1')
        {
            ft_printf("<valor permitido> '1'\n");
            return 0;
        }
        i++;
    }
    while(i < data->height)
    {
        if(data->maps2[0][i] != '1' || data->maps2[data->height - 1][i] != '1')
        {
            ft_printf("<valor permitido> '1'\n");
            return 0;
        }
        i++;
    }
    return 1;
}