#include "../Includes/cube.h"


// void	my_put_pixel(int x, int y, int color, t_cube *game)
// {
// 	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
// 		return ;
// 	int index = y * game->size_line + x * game->bpp / 8;
// 	game->data[index] = color & 0xFF;
// 	game->data[index + 1] = (color >> 8) & 0xFF;
// 	game->data[index + 2] = (color >> 16) & 0xFF;
// }

void	draw_square(int x, int y,int size, int color, t_cube *game)
{
	while (x < x + size)
	{
		// my_put_pixel(x, y, color, game);
		mlx_pixel_put(game->mlx, game->window, x, y, (mlx_color){color});
		x++;
	}
	while (y < y + size)
	{
		// my_put_pixel(x, y, color, game);
		mlx_pixel_put(game->mlx, game->window, x, y, (mlx_color){color});
		y++;
	}
	while (x > x - size)
	{
		// my_put_pixel(x, y, color, game);
		mlx_pixel_put(game->mlx, game->window, x, y, (mlx_color){color});
		x--;
	}
	while (y > y - size)
	{
		// my_put_pixel(x, y, color, game);
		mlx_pixel_put(game->mlx, game->window, x, y, (mlx_color){color});
		y--;
	}
}
