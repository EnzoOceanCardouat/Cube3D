#include "../../includes/cube.h"

bool touch(float px, float py, t_cube *game)
{
	int x = px/BLOCK;
	int y = py/BLOCK;

	if (x >= WIDTH/BLOCK || y >= HEIGHT/BLOCK || x < 0 || y < 0)
		return (true);
	if (game->map[y][x] == '1')
		return (true);
	else
		return (false);
}
