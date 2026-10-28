#include "../includes/cube.h"

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

int	get_tex_info(float ray_x, float ray_y, float cos_a, float sin_a, float *wall_x)
{
	float	prev_x = ray_x - cos_a;
	float	prev_y = ray_y - sin_a;

	if ((int)(prev_x / BLOCK) != (int)(ray_x / BLOCK))   // vertical face (E/W)
	{
		*wall_x = fmodf(ray_y, BLOCK);
		return (cos_a > 0 ? 3 : 2);                      // going right hits a WEST face
	}
	*wall_x = fmodf(ray_x, BLOCK);                       // horizontal face (N/S)
	return (sin_a > 0 ? 0 : 1);                      // going down hits a NORTH face
}
