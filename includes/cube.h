#ifndef CUBE_H
#define CUBE_H

#include "../libs/MacroLibX/includes/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

# define WIDTH 1280
# define HEIGHT 720
# define BLOCK 24

# define DEBUG 0 // Switch 2D == 1 and 3D == 0

# define W 26
# define A 4
# define S 22
# define D 7
# define LEFT 80
# define RIGHT 79
# define M 16

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
	bool m;
}	t_player;

typedef struct s_cube
{
	void *mlx;
	void *window;
	void *image;

	t_player player;
	char **map;

	mlx_image texture[4];
	int texture_width;
	int texture_height;
	mlx_color ceiling;
	mlx_color floor;

}	t_cube;

/* hook.c */
void	window_hook(int key, void *param);
void	key_hook(int key, void *param);
void	key_press(int key, void *_player);
void	key_release(int key, void *_player);

/* utils.c */
void	draw_square(int x, int y,int size, int color_switch, t_cube *game);
int		get_tex_info(float ray_x, float ray_y, float cos_a, float sin_a, float *wall_x);

/* player.c */
void	init_player(t_player *player, t_cube *game);
void	move_player(t_player *player, t_cube game);
void	loop_draw_player(void *_game);
void	draw_map(t_cube *game);
void	draw_c_and_f(t_cube *game);

/* rayCasting.c */
bool	touch(float px, float py, t_cube *game);


/* main.c */
void	draw_mini_map(t_cube *game);

#endif
