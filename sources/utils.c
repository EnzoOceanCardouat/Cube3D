#include "../Includes/cube.h"

void	draw_square(int x, int y,int size, uint32_t color, t_cube *game)
{
	int i = 0;
	int j = 0;

	while (i < size)
	{
		mlx_pixel_put(game->mlx, game->window, x + i, y, (mlx_color){.rgba = color});
		i++;
	}
	while (j < size)
	{
		mlx_pixel_put(game->mlx, game->window, x, y + j, (mlx_color){.rgba = color});
		j++;
	}
	i = 0;
	while (i <= size)
	{
		mlx_pixel_put(game->mlx, game->window, x + size, y + i, (mlx_color){.rgba = color});
		i++;
	}
	j = 0;
	while (j <= size)
	{
		mlx_pixel_put(game->mlx, game->window, x + j, y + size, (mlx_color){.rgba = color});
		j++;
	}
}
