#include "../Includes/cube.h"

void	init_player(t_player *player)
{
	player->x = WIDTH / 2;
	player->y = HEIGHT / 2;
	player->angle = PI / 2;

	player->w = false;
	player->s = false;
	player->a = false;
	player->d = false;
	player->left = false;
	player->right = false;
}

void	move_player(t_player *player)
{
	float	speed = 1;
	float	angle_speed = 0.025;
	float	cos_angle;
	float	sin_angle;

	if (player->left)
		player->angle -= angle_speed;
	if (player->right)
		player->angle += angle_speed;
	if (player->angle > 2 * PI)
		player->angle -= 2 * PI;
	else if (player->angle < 0)
		player->angle += 2 * PI;

	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);

	if (player->w)
	{
		player->x -= cos_angle * speed;
		player->y -= sin_angle * speed;
	}
	if (player->s)
	{
		player->x += cos_angle * speed;
		player->y += sin_angle * speed;
	}
	if (player->d)
	{
		player->x += sin_angle * speed;
		player->y -= cos_angle * speed;
	}
	if (player->a)
	{
		player->x -= sin_angle * speed;
		player->y += cos_angle * speed;
	}
}

void	loop_draw_player(void *_game)
{
	t_cube *game;
	game = (t_cube *)_game;
	t_player *player;

	player = &game->player;
	move_player(player);
	mlx_clear_window(game->mlx, game->window, (mlx_color){.rgba = 0x00000000});
	draw_map((t_cube *)_game);
	draw_square(player->x, player->y, 5, 0xFF00FFFF, game);
}
