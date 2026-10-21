#include "../Includes/cube.h"

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
	map[2] = "1001110000000001";
	map[3] = "1000010000000001";
	map[4] = "1001110000000001";
	map[5] = "1000000000111111";
	map[6] = "1000000000000001";
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
				draw_square(map_x, map_y, 79, 0x00FFFFFF, game);
				map_x += 79;
			}
			else
				map_x += 79;
		}
		map_x = 0;
		map_y += 79;
	}
}

void	init_cube(t_cube *game)
{
	mlx_window_create_info info = {0};

	info.title = "Cube3D";
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
	game->image = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->image)
	{
		free_mlx(game->mlx);
		exit(1);
	}
	mlx_put_image_to_window(game->mlx, game->window, game->image, 0, 0);
	init_player(&game->player);
	game->map = init_map();
}

int	main()
{
	t_cube game;

	init_cube(&game);

	//draw_square(WIDTH/2 - 5, HEIGHT/2 - 5, 11, 0xFF00FFFF, &game);

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
