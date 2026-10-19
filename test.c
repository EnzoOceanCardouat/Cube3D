#include "MacroLibX/includes/mlx.h"
#include "MacroLibX/includes/mlx_extended.h"
#include <stdio.h>


void key_hook(int key, void *param) {
	if (key == 41)
		mlx_loop_end((mlx_context)param);
}


void mouse_tacker(mlx_context *mlx, mlx_window *window) {
	int mouse_x;
	int mouse_y;

	mlx_mouse_get_pos(*mlx, &mouse_x, &mouse_y);
	printf("x: %d,y: %d\n", mouse_x, mouse_y);
	mlx_pixel_put(*mlx, *window, mouse_x, mouse_y, (mlx_color){.rgba = 0x00FFFFFF});
}

int main()
{
	mlx_context mlx = mlx_init();
	mlx_window_create_info info = {0};

	info.title = "Cube 3D";
	info.height = 400;
	info.width = 800;

	mlx_window window;
	window = mlx_new_window(mlx, &info);

	for (int x = 375; x < 425; x++)
		for (int y = 175; y < 225; y++)
			mlx_pixel_put(mlx, window, x, y, (mlx_color){.rgba = 0xFF00FFFF});

	mlx_color pixel[50 * 50] = {0};

	int x = 0;

	for (int i = 0; i < 50; i++) {
		for (int j =0; j < 50; j++, i++)
			pixel[i].rgba = 0xFFFF00FF;
	}

	mlx_pixel_put_array(mlx, window, 25, 25, pixel, 50 *50);
	mlx_pixel_put_region(mlx, window, 725, 325, 50, 50, pixel);

	mlx_on_event(mlx, window,MLX_KEYDOWN, key_hook, mlx);

	mlx_loop(mlx);
	mouse_tacker(&mlx, &window);
	mlx_destroy_window(mlx, window);
	mlx_destroy_context(mlx);
}
