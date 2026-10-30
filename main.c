/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecardoua <ecardoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 17:26:36 by ecardoua          #+#    #+#             */
/*   Updated: 2026/10/30 16:21:11 by ecardoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube.h"

void	free_mlx(t_cube *game)
{
	if (game->image)
		mlx_destroy_image(game->mlx, game->image);
	if (game->window)
		mlx_destroy_window(game->mlx, game->window);
	if (game->mlx)
	{
		mlx_destroy_context(game->mlx);
		free(game->mlx);
	}
	game = NULL;
}

char **init_map(void)
{
	char **map;

	map = malloc(10 * sizeof(char *));
	map[0] = "1111111111111111";
	map[1] = "1000000000000001";
	map[2] = "1001110000010001";
	map[3] = "1000010011000101";
	map[4] = "1001110000010001";
	map[5] = "1000000000111111";
	map[6] = "100000N000000001";
	map[7] = "1000000000000001";
	map[8] = "1111111111111111";
	map[9] = NULL;
	return (map);
}

void	draw_map(t_cube *game)
{
	int map_x = 0;
	int map_y = 0;

	for (int i =0; game->map[i]; i++)
	{
		for (int j =0; game->map[i][j];j++)
		{
			if (game->map[i][j] == '1')
			{
				draw_square(map_x, map_y, BLOCK, 0x00FFFFFF, game);
				map_x += BLOCK;
			}
			else if (game->player.spawn == false && (game->map[i][j] == 'N' || game->map[i][j] == 'S' || game->map[i][j] == 'E' || game->map[i][j] == 'W'))
			{
				game->player.x = ((j * BLOCK) + BLOCK) - BLOCK/2;
				game->player.y = ((i * BLOCK) + BLOCK) - BLOCK/2;
				game->player.spawn_direction = game->map[i][j];
				map_x += BLOCK;
				game->player.spawn = true;
			}
			else
				map_x += BLOCK;
		}
		map_x = 0;
		map_y += BLOCK;
	}
}

void	draw_player_mini_map(t_cube *game)
{
	const char	*template[] = {"0001000", "0001000", "0011100", "0011100",
		"0111110", "0111110", "1111111", "1111111", "1110111", "0100010"};
	int	map_size;
	int	origin_x;
	int	origin_y;
	int	i;
	int	j;


	map_size = BLOCK / 2;
	origin_x = 50 + (game->player.x * map_size) / BLOCK - 7  / 2;
	origin_y = 50 + (game->player.y * map_size) / BLOCK - 10 / 2;
	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 7)
		{
			if (template[i][j] == '1')
				mlx_pixel_put(game->mlx, game->window, origin_x + j, origin_y + i, (mlx_color){.rgba = 0xFF1493FF});
			j++;
		}
		i++;
	}
}

void	draw_mini_map(t_cube *game)   
{
	int x;
	int y;
	int i;
	int j;
	int size;

	y = 50;
	i = 0;
	size = BLOCK / 2;
	while (game->map[i])
	{
		x = 50;
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == '1')
				draw_square(x, y, size, j + i, game);
			x += size;
			j++;
		}
		y+= size;
		i++;
	}
	draw_player_mini_map(game);
}

void	load_texture(t_cube *game)
{
	char *path[4];
	int i;

	path[0] = "texture/NO.png";
	path[1] = "texture/SO.png";
	path[2] = "texture/EA.png";
	path[3] = "texture/WE.png";
	i = 0;

	while (i < 4)
	{
		game->texture[i] = mlx_new_image_from_file(game->mlx, path[i], &game->texture_width, &game->texture_height);
		if (!game->texture[i])
		{
			while (--i >= 0)
				mlx_destroy_image(game->mlx, game->texture[i]);
			// ADD CLEAN EXIT
			exit(1);
		}
		i++;
	}
}

void	init_cube(t_cube *game)
{
	mlx_window_create_info info = {0};

	info.title = "Cub3D";
	info.height = HEIGHT;
	info.width = WIDTH;

	game->mlx = mlx_init();
	if (!game->mlx)
		exit(1);
	game->window = mlx_new_window(game->mlx, &info);
	if (!game->window)
	{
		free_mlx(game->mlx);
		exit(1);
	}
	game->image = mlx_new_image(game->mlx, (int)WIDTH, (int)HEIGHT);
	if (!game->image)
	{
		free_mlx(game->mlx);
		exit(1);
	}
	mlx_put_image_to_window(game->mlx, game->window, game->image, 0, 0);
	game->map = init_map();
	load_texture(game);
	game->ceiling = (mlx_color){.rgba = 0x448EE4FF};
	game->floor = (mlx_color){.rgba = 0x00C04BFF};
	init_player(&game->player, game);
}

void	loop_free_map(t_cube *game)
{
	int i;

	i = 0;
	while (game->map[i])
		i++;
	free(game->map[i]);
}

int	main()
{
	t_cube game;

	init_cube(&game);

	mlx_on_event(game.mlx, game.window, MLX_KEYDOWN, key_hook, (void *)game.mlx);
	mlx_on_event(game.mlx, game.window, MLX_WINDOW_EVENT, window_hook, (void *)&game);
	mlx_on_event(game.mlx, game.window, MLX_KEYDOWN, key_press, (void *)&game);
	mlx_on_event(game.mlx, game.window, MLX_KEYUP, key_release, (void *)&game);

	mlx_add_loop_hook(game.mlx, loop_draw_player, &game);
	mlx_loop(game.mlx);

	loop_free_map(&game);
	mlx_destroy_image(game.mlx, game.texture[0]);
	mlx_destroy_image(game.mlx, game.texture[1]);
	mlx_destroy_image(game.mlx, game.texture[2]);
	mlx_destroy_image(game.mlx, game.texture[3]);
	mlx_destroy_window(game.mlx, game.window);
	mlx_destroy_image(game.mlx, game.image);
	mlx_destroy_context(game.mlx);
}
