#ifndef PARSING_H
#define PARSING_H

#include "cube.h"
#include "Libft/libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);

typedef struct	s_info_data
{
	char		*north_texture;
	char		*south_texture;
	char		*west_texture;
	char		*east_texture;
	mlx_color	floor_color;
	mlx_color	cellar_color;
}	t_info_data;

#endif
