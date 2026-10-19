#include "MacroLibX/includes/mlx.h"

int main()
{
	mlx_context mlx = mlx_init();
	mlx_window_create_info info = {0};

	info.title = "Cube 3D";
	info.height = 720;
	info.width = 1080;

	mlx_window window;
	window = mlx_new_window(mlx, &info);
	mlx_loop(mlx);
}
