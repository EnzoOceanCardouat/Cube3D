#ifndef CUBE_H
#define CUBE_H

#include "../MacroLibX/includes/mlx.h"
#include <stdlib.h>

# define WIDTH 1280
# define HEIGHT 720

typedef struct s_cube
{
	void *mlx;
	void *window;
	void *image;

	char *data;
	int bpp;
	int size_line;
	int endian;

}	t_cube;

void	window_hook(int key, void *param);
void	key_hook(int key, void *param);

void	my_put_pixel(int x, int y, int color, t_cube *game);
void	draw_square(int x, int y,int size, int color, t_cube *game);

#endif
