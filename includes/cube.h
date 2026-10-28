#ifndef CUBE_H
#define CUBE_H

#include "../includes/MacroLibX/includes/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

# define WIDTH 1280
# define HEIGHT 720
# define BLOCK 80

# define DEBUG 0 // Switch 2D == 1 and 3D == 0

# define W 26
# define A 4
# define S 22
# define D 7
# define LEFT 80
# define RIGHT 79

# define IMG_WIDTH 80
# define IMG_HEIGHT 80

typedef struct s_player
{
	float x;
	float y;
	float angle;
	char spawn_direction;

	bool w;
	bool s;
	bool a;
	bool d;
	bool left;
	bool right;
	bool spawn;
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

	mlx_image texture[4];
	int texture_width;
	int texture_height;

}	t_cube;

void	window_hook(int key, void *param);
void	key_hook(int key, void *param);
void	key_press(int key, void *_player);
void	key_release(int key, void *_player);

/*utils.c*/
void	draw_square(int x, int y,int size, uint32_t color, t_cube *game);
int		get_tex_info(float ray_x, float ray_y, float cos_a, float sin_a, float *wall_x);


void	init_player(t_player *player, t_cube *game);
void	move_player(t_player *player, t_cube game);
void	loop_draw_player(void *_game);
void	draw_map(t_cube *game);

bool	touch(float px, float py, t_cube *game);

#endif
