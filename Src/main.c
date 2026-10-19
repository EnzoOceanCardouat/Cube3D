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
}

int	main()
{
	t_cube game;

	init_cube(&game);

	mlx_on_event(game.mlx, game.window, MLX_KEYDOWN, key_hook, game.mlx);
	mlx_on_event(game.mlx, game.window, MLX_WINDOW_EVENT, window_hook, game.mlx);
	draw_square(WIDTH/2, HEIGHT/2, 10, 0xFF00FFFF, &game);
	mlx_loop(game.mlx);

	mlx_destroy_window(game.mlx, game.window);
	mlx_destroy_image(game.mlx, game.image);
	mlx_destroy_context(game.mlx);
}
