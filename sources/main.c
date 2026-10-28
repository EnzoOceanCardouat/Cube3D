#include "../includes/cube.h"

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

void	load_texture(t_cube *game)
{
	char *path[4];
	int i;

	path[0] = "sources/NO.png";
	path[1] = "sources/SO.png";
	path[2] = "sources/EA.png";
	path[3] = "sources/WE.png";
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
	init_player(&game->player, game);
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

	mlx_destroy_window(game.mlx, game.window);
	mlx_destroy_image(game.mlx, game.image);
	mlx_destroy_context(game.mlx);
}
