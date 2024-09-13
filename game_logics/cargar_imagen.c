/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cargar_imagen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dediaz-f <dediaz-f@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:20:08 by dediaz-f          #+#    #+#             */
/*   Updated: 2024/07/29 17:20:08 by dediaz-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int cargar_imagen(t_mapa *data, void **img, char *ruta) { 
    int img_width;
    int img_height;

    if (data == NULL || data->mlx == NULL) {
        fprintf(stderr, "Error: data o data->mlx es NULL.\n");
        return 1;
    }

    printf("Cargando imagen desde: %s\n", ruta);
    *img = mlx_xpm_file_to_image(data->mlx, ruta, &img_width, &img_height);
    if (*img == NULL) {
    fprintf(stderr, "Error al cargar la imagen: %s\n", ruta);
        return 1;
    }

    printf("Imagen cargada exitosamente.\n");
    return 0;
}