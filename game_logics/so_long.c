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

int	frame_s(t_mapa *data)
{
	mlx_clear_window(data->mlx, data->win);
	dibujo_mapa(data);
	if (data->colectables == 0 && data->player == 1 && data->finish == 1)
	{
		ft_game_result(data);
		ft_printf("FINAL!\n");
	}
	return (0);
}

void check_general(t_mapa *data)
{
	int	j;
	int	i;
	int	element;

	i = 0;
	j = 0;
	element = 0;
	comprobacion_open_ber(data);
	//verificar_linea(data);
	caracter_valido(data);
	objetos_de_mapa(data);
	es_posible(data, j, i, element);
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

int	main(int argc, char *argv[])
{
	t_mapa	*data;

	// Verificar si se ha pasado el argumento correctamente
	if (argc != 2)
	{
		ft_printf("Uso: %s <nombre.ber>\n", argv[0]);
		return (1);
	}

	// Intentar asignar memoria para la estructura t_mapa
	data = (t_mapa *)malloc(sizeof(t_mapa));
	if (data == NULL)
	{
		ft_printf("Error en la asignación de memoria para la estructura t_mapa.\n");
		return (EXIT_FAILURE);
	}
	ft_printf("Memoria asignada correctamente para la estructura t_mapa.\n");

	// Inicializar la estructura con 0
	data = (t_mapa *)memset(data, 0, sizeof(t_mapa));
	ft_printf("Estructura t_mapa inicializada con 0.\n");

	// Inicializar el entorno de mlx
	data->mlx = mlx_init();
	if (data->mlx == NULL)
	{
		ft_printf("Error al inicializar mlx.\n");
		free(data);
		return (EXIT_FAILURE);
	}
	ft_printf("mlx inicializado correctamente.\n");

	// Llamar a las funciones para cargar y validar el mapa
	llamada_funciones(data, argv);
	ft_printf("Funciones del mapa llamadas exitosamente.\n");

	// Crear una nueva ventana con las dimensiones apropiadas
	data->win = mlx_new_window(data->mlx, data->width * SPRITE_SIZE,
			data->height * SPRITE_SIZE, "so_long");
	if (data->win == NULL)
	{
		ft_printf("Error al crear la ventana de mlx.\n");
		free(data);
		return (EXIT_FAILURE);
	}
	ft_printf("Ventana de mlx creada correctamente. Tamaño: %dx%d.\n", 
			data->width * SPRITE_SIZE, data->height * SPRITE_SIZE);

	// Inicializar las variables relacionadas con la animación
	data->player_frame = 0;
	data->total_frames = 3;
	ft_printf("Animación inicializada. Player frame: %d, Total frames: %d.\n",
			data->player_frame, data->total_frames);

	// Configurar los eventos para cerrar la ventana y para teclas
	mlx_hook(data->win, 17, 0, exit_game, (void *)data);
	mlx_key_hook(data->win, key_hook, (void *)data);
	ft_printf("Eventos de mlx configurados (cerrar ventana y teclas).\n");

	// Llamada para manejar los cuadros de animación
	frame_s(data);
	ft_printf("Animación de los cuadros gestionada.\n");

	// Ejecutar el loop de mlx
	mlx_loop(data->mlx);
	ft_printf("Loop de mlx iniciado.\n");

	// Liberar memoria al finalizar
	free(data->imagenes);
	ft_printf("Memoria de imagenes liberada.\n");

	free(data);
	ft_printf("Memoria de t_mapa liberada.\n");

	return (0);
}