#include "../Includes/cube.h"

void	init_player(t_player *player)
{
	player->x = WIDTH / 2;
	player->y = HEIGHT / 2;
	//player->angle = PI / 2;

	player->w = false;
	player->s = false;
	player->a = false;
	player->d = false;
	// player->left = false;
	// player->right = false;
}

void	key_press(int key, void *_player)
{
	t_cube *cube;
	cube = (t_cube *)_player;
	t_player *player;
	player = (t_player *)&cube->player;
	if (key == W)
		player->w = true;
	else if (key == S)
		player->s = true;
	else if (key == A)
		player->a = true;
	else if (key == D)
		player->d = true;
	// else if (key == LEFT)
	// 	player->left = true;
	// else if (key == RIGHT)
	// 	player->right = true;
}

void	key_release(int key, void *_player)
{
	t_cube *cube;
	cube = (t_cube *)_player;
	t_player *player;
	player = (t_player *)&cube->player;
	if (key == W)
		player->w = false;
	else if (key == S)
		player->s = false;
	else if (key == A)
		player->a = false;
	else if (key == D)
		player->d = false;
	// else if (key == LEFT)
	// 	player->left = false;
	// else if (key == RIGHT)
	// 	player->right = false;
}

void	move_player(t_player *player)
{
	int speed = 1;
	// float angle_speed = 0.1;
	// float cos_angle = cos(player->angle);
	// float sin_angle = sin(player->angle);

	// if (player->left)
	// 	player->angle -= angle_speed;
	// else if (player->right)
	// 	player->angle += angle_speed;
	// else if (player->angle > 2 * PI)
	// 	player->angle = 0;
	// else if (player->angle < 0)
	// 	player->angle = 2 * PI;
	// if (player->w)
	// {
	// 	player->x += cos_angle * speed;
	// 	player->x += sin_angle * speed;
	// }
	// else if (player->s)
	// {
	// 	player->x -= cos_angle * speed;
	// 	player->x -= sin_angle * speed;
	// }
	// else if (player->a)
	// {
	// 	player->x += cos_angle * speed;
	// 	player->x -= sin_angle * speed;
	// }
	// else if (player->d)
	// {
	// 	player->x -= cos_angle * speed;
	// 	player->x += sin_angle * speed;
	// }
	if (player->w)
		player->y -= speed;
	else if (player->s)
		player->y +=speed;
	else if (player->a)
		player->x -=speed;
	else if (player->d)
		player->x +=speed;
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
