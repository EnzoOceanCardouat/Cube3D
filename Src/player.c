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

void	move_player(t_player *player, t_cube game)
{
	float	speed = 1.5;
	float	angle_speed = 0.025;
	float	cos_angle;
	float	sin_angle;
	float	new_x;
	float	new_y;

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
		new_x = player->x + cos_angle * speed;
		new_y = player->y + sin_angle * speed;
		if (!touch(new_x, new_y, &game))
		{
			player->x = new_x;
			player->y = new_y;
		}
	}
	if (player->s)
	{
		new_x = player->x - cos_angle * speed;
		new_y = player->y - sin_angle * speed;
		if (!touch(new_x, new_y, &game))
		{
			player->x = new_x;
			player->y = new_y;
		}
	}
	if (player->d)
	{
		new_x = player->x - sin_angle * speed;
		new_y = player->y + cos_angle * speed;
		if (!touch(new_x, new_y, &game))
		{
			player->x = new_x;
			player->y = new_y;
		}
	}
	if (player->a)
	{
		new_x = player->x + sin_angle * speed;
		new_y = player->y - cos_angle * speed;
		if (!touch(new_x, new_y, &game))
		{
			player->x = new_x;
			player->y = new_y;
		}
	}
}

float distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

float fix_distance(float x2, float x1, float y2, float y1, t_cube *game)
{
	float delta_x = x2 - x1;
	float delta_y = y2 - y1;
	float angle = atan2(delta_y, delta_x) - game->player.angle;
	float fix_dist = distance(delta_x, delta_y) * cos(angle);
	return (fix_dist);
}

void draw_line(t_player *player, t_cube *game, float start_x, int i)
{
	float cos_angle = cos(start_x);
	float sin_angle = sin(start_x);
	float ray_x = player->x;
	float ray_y = player->y;

	while (!touch(ray_x, ray_y, game))
	{
		if (DEBUG == 1)
			mlx_pixel_put(game->mlx, game->window, ray_x, ray_y, (mlx_color){.rgba = 0xFFFFFFFF});
		ray_x += cos_angle;
		ray_y += sin_angle;
	}

	if (DEBUG == 1)
		return;
	float dist = fix_distance(ray_x, player->x, ray_y, player->y, game);
	float height = (BLOCK / dist) * (WIDTH / 2);
	int start_y = (HEIGHT - height) / 2;
	int end = start_y + height;

	while (start_y < end)
	{
		mlx_pixel_put(game->mlx, game->window, i, start_y, (mlx_color){.rgba = 0x00FFFFFF});
		start_y++;
	}
}

void	loop_draw_player(void *_game)
{
	t_player *player;

	player = &((t_cube *)_game)->player;
	move_player(player, *(t_cube *)_game);
	mlx_clear_window(((t_cube *)_game)->mlx, ((t_cube *)_game)->window, (mlx_color){.rgba = 0x00000000});
	if (DEBUG == 1)
	{
		draw_map((t_cube *)_game);
		draw_square(player->x, player->y, 5, 0xFF00FFFF, (t_cube *)_game);
	}
	float fraction = PI / 3 / WIDTH;
	float start_x = player->angle - PI /6;
	int i =0;
	while (i < WIDTH)
	{
		draw_line(player, (t_cube *)_game, start_x, i);
		start_x += fraction;
		i++;
	}
}
