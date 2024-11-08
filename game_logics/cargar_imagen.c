/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cargar_imagen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dediaz-f <dediaz-f@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:20:08 by dediaz-f          #+#    #+#             */
/*   Updated: 2024/11/07 12:33:13 by dediaz-f         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "so_long.h"

int	cargar_imagen(t_mapa *data, void **img, char *ruta)
{
	int	img_width;
	int	img_height;

	if (data == NULL || data->mlx == NULL)
	{
		fprintf(stderr, "Error: data o data->mlx es NULL.\n");
		return (1);
	}
	ft_printf("Cargando imagen desde: %s\n", ruta);
	*img = mlx_xpm_file_to_image(data->mlx, ruta, &img_width, &img_height);
	if (*img == NULL)
	{
		fprintf(stderr, "Error al cargar la imagen: %s\n", ruta);
		return (1);
	}
	ft_printf("Imagen cargada exitosamente.\n");
	return (0);
}

int	cargar_imagenes(t_mapa *data)
{
	ft_printf("Intentando cargar imágenes...\n");
	data->imagenes = (t_imagenes *)malloc(sizeof(t_imagenes));
	if (data->imagenes == NULL)
	{
		ft_printf("Error al asignar memoria para imágenes.\n");
		return (1);
	}
	if (cargar_imagen(data, &(data->imagenes->wall), WALL_IMAGE)) return 1;
	if (cargar_imagen(data, &(data->imagenes->space), SPACE_IMAGE)) return 1;
	if (cargar_imagen(data, &(data->imagenes->player_frame1), PLAYER_F1)) return 1;
	if (cargar_imagen(data, &(data->imagenes->player_frame2), PLAYER_F2)) return 1;
	if (cargar_imagen(data, &(data->imagenes->player_frame3), PLAYER_F3)) return 1;
	if (cargar_imagen(data, &(data->imagenes->collect), COLLECT1_IMAGE)) return 1;
	if (cargar_imagen(data, &(data->imagenes->collect2), COLLECT2_IMAGE)) return 1;
	if (cargar_imagen(data, &(data->imagenes->exit), EXIT_IMAGE)) return 1;
	if (cargar_imagen(data, &(data->imagenes->fuego1), FIRE1_IMAGE)) return 1;
	if (cargar_imagen(data, &(data->imagenes->fuego2), FIRE2_IMAGE)) return 1;
	ft_printf("Todas las imágenes cargadas correctamente.\n");
	return (0);
}

void llamada_funciones(t_mapa *data, char **argv)
{
	reset_data(data, argv[1]);
	mapa_size(data);
	read_map(data);
	//check_general(data);
}

void manejar_error_fd(const char *mensaje, int fd, char *line)
{
    if (line != NULL)
        free(line);     // Libera la línea si está en memoria
    if (fd >= 0)
        close(fd);      // Cierra el archivo
    fprintf(stderr, "%s\n", mensaje);
    exit(EXIT_FAILURE);
}