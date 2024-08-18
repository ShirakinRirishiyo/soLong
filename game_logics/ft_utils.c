#include "so_long.h"

void ft_printear(unsigned int n)
{
    char *str = ft_itoa(n); // Convierte el número a cadena
    if (str) 
    {
        ft_printf("Número de pasos: %s\n", str); // Imprime la cadena
        free(str); // Libera la memoria de la cadena
    } else 
    {
        ft_printf("Error al convertir el número de pasos.\n");
    }
}
int exit_game(t_mapa *data)
{
	mlx_destroy_window(data->mlx, data->win);
	exit(EXIT_SUCCESS);
}
void draw_grid(t_mapa *data)
{
    int i;
    int j;

    i = 0;
    while(i < data->height)
    {
        j = 0;
        while(j < data->width)
        {
            mlx_pixel_put(data->mlx, data->win, j * 40, i * 40, 0xFFFFFF); // Dibuja un punto blanco
        }
        j++;
    }
    i++;
}
void ft_game_result(t_mapa *data)
{
    mlx_clear_window(data->mlx, data->win);
    draw_grid(data); // Dibuja una rejilla para ayudar a la visualización
    int x = data->width * 40 / 2.4;
    int y = data->height * 40 / 4;

    // Imprime las coordenadas en la consola para depuración
    printf("Dibujando resultado en (%d, %d)\n", x, y);
    
    mlx_put_image_to_window(data->mlx, data->win, data->imagenes->player_down, x, y);
}

void actualizar_pantalla(t_mapa *data)
{
    // Redibuja todo el mapa
    dibujo_mapa(data);
}
void actualizar_animacion_fuego(t_mapa *data)
{
    static int contador;
    
    contador = 0;  
    contador++;
    if (contador > 5) // Cambiar cada 10 cuadros, ajusta según tus necesidades
    {
        data->animacion_fuego = !data->animacion_fuego;
        contador = 0;
    }
}

int write_itoa(int n)
{
    char *str = ft_itoa(n);
    if (str)
    {
        write(1, str, ft_strlen(str)); // Cambia esto a tu función de impresión
        free(str);
    }
    return 0;
}
