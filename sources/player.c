#include "../includes/cube.h"

void init_pos_player(t_player *player, t_cube *game)
{
	int i;
	int j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'N' || game->map[i][j] == 'S' || game->map[i][j] == 'E' || game->map[i][j] == 'W')
			{
				player->x = ((j * BLOCK) + BLOCK) - BLOCK/2;
				player->y = ((i * BLOCK) + BLOCK) - BLOCK/2;
				player->spawn_direction = game->map[i][j];
			}
			j++;
		}
		i++;
	}
}

void	init_player(t_player *player, t_cube *game)
{
	init_pos_player(player, game);
	if (player->spawn_direction == 'N')
		player->angle = (3 * M_PI / 2);
	else if (player->spawn_direction == 'S')
		player->angle = (M_PI / 2);
	else if (player->spawn_direction == 'W')
		player->angle = M_PI;
	else if (player->spawn_direction == 'E')
		player->angle = 0;

	player->w = false;
	player->s = false;
	player->a = false;
	player->d = false;
	player->left = false;
	player->right = false;
	player->spawn = false;
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
	if (player->angle > 2 * M_PI)
		player->angle -= 2 * M_PI;
	else if (player->angle < 0)
		player->angle += 2 * M_PI;

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
	float top = (HEIGHT - height) / 2;

	float wall_x;
	int   t = get_tex_info(ray_x, ray_y, cos_angle, sin_angle, &wall_x);

	int tex_x = (int)(wall_x / BLOCK * game->texture_width);
	if (tex_x >= game->texture_width)
		tex_x = game->texture_width - 1;

	int y = (top < 0) ? 0 : (int)top;
	int end = (top + height > HEIGHT) ? HEIGHT : (int)(top + height);

	while (y < end)
	{
		int tex_y = (int)((y - top) * game->texture_height / height);
		if (tex_y >= game->texture_height)
			tex_y = game->texture_height - 1;
		mlx_color color = mlx_get_image_pixel(game->mlx, game->texture[t], tex_x, tex_y);
		mlx_pixel_put(game->mlx, game->window, i, y, color);
		y++;
	}
	// float dist = fix_distance(ray_x, player->x, ray_y, player->y, game);
	// float height = (BLOCK / dist) * (WIDTH / 2);
	// int start_y = (HEIGHT - height) / 2;
	// int end = start_y + height;

	// while (start_y < end)
	// {
	// 	mlx_pixel_put(game->mlx, game->window, i, start_y, (mlx_color){.rgba = 0xFF00FFFF});
	// 	start_y++;
	// }
}

void	loop_draw_player(void *_game)
{
	move_player(&((t_cube *)_game)->player, *(t_cube *)_game);
	mlx_clear_window(((t_cube *)_game)->mlx, ((t_cube *)_game)->window, (mlx_color){.rgba = 0x00000000});
	if (DEBUG == 1)
	{
		draw_map((t_cube *)_game);
		draw_square(((t_cube *)_game)->player.x, ((t_cube *)_game)->player.y, 5, 0xFF00FFFF, (t_cube *)_game);
	}
	float fraction = M_PI / 3 / WIDTH;
	float start_x = ((t_cube *)_game)->player.angle - M_PI / 6;
	int i =0;
	while (i < WIDTH)
	{
		draw_line(&((t_cube *)_game)->player, (t_cube *)_game, start_x, i);
		start_x += fraction;
		i++;
	}
}
