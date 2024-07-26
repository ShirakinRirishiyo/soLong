#include "so_long.h"

void ft_printear(unsigned int n)
{
	ft_itoa(n);
	ft_printf("Numero de pasos: %d\n");
}

void exit_game(t_mapa *data)
{
	mlx_destroy_window(data->mlx, data->win);
	exit(EXIT_SUCCES);
}
void	ft_game_result(t_info_map *data)
{
	mlx_clear_window(data->mlx, data->win);
	mlx_put_image_to_window(data->mlx, data->win, data->images->winner,
		data->width * 40 / 2.4, data->hight * 40 / 4);
}