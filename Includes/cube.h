#ifndef CUBE_H
#define CUBE_H

#include "../MacroLibX/includes/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

# define WIDTH 1280
# define HEIGHT 720

# define W 26
# define A 4
# define S 22
# define D 7
# define LEFT 80
# define RIGHT 79

# define PI 3.14159265359

typedef struct s_player
{
	float x;
	float y;
	// float angle;

	bool w;
	bool s;
	bool a;
	bool d;
	// bool left;
	// bool right;
}	t_player;

typedef struct s_cube
{
	void *mlx;
	void *window;
	void *image;

	char *data;
	int bpp;
	int size_line;
	int endian;

	t_player player;
	char **map;
}	t_cube;

void	window_hook(int key, void *param);
void	key_hook(int key, void *param);

void	draw_square(int x, int y,int size, uint32_t color, t_cube *game);

void	init_player(t_player *player);
void	key_press(int key, void *_player);
void	key_release(int key, void *_player);
void	move_player(t_player *player);
void	loop_draw_player(void *_game);
void	draw_map(t_cube *game);

#endif
