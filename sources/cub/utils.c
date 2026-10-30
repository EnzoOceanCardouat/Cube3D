#include "../../includes/cube.h"

void	draw_square(int x, int y,int size, int color_switch, t_cube *game)
{
	int i;
	int j;
	mlx_color gray;
	mlx_color lightGray;

	i = 0;
	gray = (mlx_color){.rgba = 0x808080FF};
	lightGray = (mlx_color){.rgba = 0xD3D3D3FF};
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (color_switch % 2 == 1)
				mlx_pixel_put(game->mlx, game->window, x + i, y + j, gray);
			else
				mlx_pixel_put(game->mlx, game->window, x + i, y + j, lightGray);
			j++;
		}
		i++;
	}
}

int	get_tex_info(float ray_x, float ray_y, float cos_a, float sin_a, float *wall_x)
{
	float	prev_x = ray_x - cos_a;
	float	prev_y = ray_y - sin_a;

	if ((int)(prev_x / BLOCK) != (int)(ray_x / BLOCK))
	{
		*wall_x = fmodf(ray_y, BLOCK);
		return (cos_a > 0 ? 3 : 2);
	}
	*wall_x = fmodf(ray_x, BLOCK);
	return (sin_a > 0 ? 0 : 1);
}
