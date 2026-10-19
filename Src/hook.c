#include "../Includes/cube.h"

void	key_hook(int key, void *param)
{
	if (key == 41)
		mlx_loop_end((mlx_context)param);
}

void	window_hook(int key, void *param)
{
	if (key == 0)
		mlx_loop_end((mlx_context)param);
}
