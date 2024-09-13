/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dediaz-f <dediaz-f@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:48:41 by dediaz-f          #+#    #+#             */
/*   Updated: 2024/07/29 14:48:41 by dediaz-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*void print_map(t_mapa *data)
{
    int i;

    i = 0;
    while (data->map[i])
     {
        printf("%s\n", data->map[i]);
        i++;
    }
}*/

int cargar_imagenes(t_mapa *data) 
{
    printf("Intentando cargar imágenes...\n");

    data->imagenes = (t_imagenes *)malloc(sizeof(t_imagenes));
    if (data->imagenes == NULL) 
    {
        printf("Error al asignar memoria para imágenes.\n");
        return 1;
    }
    // Cargar las imágenes usando las rutas definidas
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

    printf("Todas las imágenes cargadas correctamente.\n");
    return 0;
}

void reset_data(t_mapa *data, char *name) 
{
    printf("Restableciendo datos...\n");

    // data->height = 0;
    // data->width = 0;
    // data->x = 0;
    // data->y = 0;
    // data->player = 0;
    // data->colectables = 0;
    // data->pasos = 0;
    // data->finish = 0;
    data->text = name;
    cargar_imagenes(data);
}


int frame_s(t_mapa *data) {
    // Limpiar la ventana con el color de fondo
    mlx_clear_window(data->mlx, data->win);

    // Establecer el color de fondo
    // mlx_put_image_to_window(data->mlx, data->win, data->background_img, 0, 0);

    // Dibujar el mapa
    dibujo_mapa(data);

    // Comprobar si el juego ha terminado
    if (data->colectables == 0 && data->player == 1 && data->finish == 1) {
        ft_game_result(data);
    }
    return 0;
}


void check_general(t_mapa *data) 
{
    printf("Verificando el mapa...\n");
    int j;
    int i;
    int element;

    comprobacion_open_ber(data);
    verificar_linea(data);
    caracter_valido(data);
    objetos_de_mapa(data);
    j = 0;
    i = 0;
    element = 0;
    es_posible(data, j, i, element);
    printf("Verificación del mapa completada.\n");
}

int main(int argc, char *argv[]) 
{
    t_mapa *data;

    if (argc != 2) 
    {
        printf("Uso: %s <nombre.ber>\n", argv[0]);
        return 1;
    }
	printf("Asignando memoria para data...\n");
	data = (t_mapa *)malloc(sizeof(t_mapa));
	data = (t_mapa *)memset(data, 0, sizeof(t_mapa));
	if (data == NULL) 
	{
		perror("Error al asignar memoria para data");
		return EXIT_FAILURE;
	}
	printf("Inicializando MiniLibX...\n");
	data->mlx = mlx_init();
	if (data->mlx == NULL) 
	{
		perror("Error al inicializar MiniLibX");
		free(data);
		return EXIT_FAILURE;
	}
	// data->imagenes = NULL; // Asegúrate de inicializar punteros
	// data->win = NULL;      // Asegúrate de inicializar punteros
	printf("Restableciendo datos...\n");
	reset_data(data, argv[1]);
	printf("Calculando el tamaño del mapa...\n");
	mapa_size(data);
	printf("Leyendo el mapa...\n");
	read_map(data);
	printf("Verificando el mapa...\n");
	check_general(data);
	printf("Creando la ventana...\n");
	data->win = mlx_new_window(data->mlx, data->width * SPRITE_SIZE, data->height * SPRITE_SIZE, "so_long");
	if (data->win == NULL) 
	{
		perror("Error al crear la ventana");
		free(data);
		return EXIT_FAILURE;
	}
	printf("Configurando hooks...\n");
	mlx_hook(data->win, 17, 0, exit_game, (void *)data);
	mlx_key_hook(data->win,/*  2, 0,  */key_hook, (void *)data);
	frame_s(data);
	// mlx_loop_hook(data->mlx, frame_s, (void *)data);
	printf("Entrando en el bucle principal...\n");
	mlx_loop(data->mlx);
	printf("Liberando memoria...\n");
	// Asegúrate de liberar cualquier memoria adicional que hayas asignado
	free(data->imagenes);  // Si imagenes es una estructura o un array, debes liberar correctamente cada miembro
	free(data);
    return 0;
}
