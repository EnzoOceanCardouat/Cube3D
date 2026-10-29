/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/22 13:05:46 by mcrenn            #+#    #+#             */
/*   Updated: 2026/10/27 11:15:19 by mcrenn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

int parsing(int fd)
{
	char		*str;
	t_info_data	*data;
	char		**floor;
	char		**ceiling;

	int fd = open("test.txt", O_RDONLY);
	data = ft_calloc(1, sizeof(t_info_data));

	// protection fd

	str = get_next_line(fd);
	while (str)
	{
		if (ft_strncmp("NO ", str, 3) == 0)
		{
			data->north_texture = ft_substr(str, 3, ft_strlen(str) - 4);
		}
		//else error
		if (ft_strncmp("SO ", str, 3) == 0)
			data->south_texture = ft_substr(str, 3, ft_strlen(str) - 4);
		if (ft_strncmp("WE ", str, 3) == 0)
			data->west_texture = ft_substr(str, 3, ft_strlen(str) - 4);
		if (ft_strncmp("EA ", str, 3) == 0)
			data->east_texture = ft_substr(str, 3, ft_strlen(str) - 4);
		if (ft_strncmp("F ", str, 2) == 0)
		{
			/* TODO Error managing:
				- Checking the validity of the atoi
			*/
			floor = ft_split(str + 2, ',');
			data->floor_color.r = ft_atoi(floor[0]);
			data->floor_color.g = ft_atoi(floor[1]);
			data->floor_color.b = ft_atoi(floor[2]);
		}
		if (ft_strncmp("C ", str, 2) == 0)
		{
			ceiling = ft_split(str + 2, ',');
			data->cellar_color.r = ft_atoi(ceiling[0]);
			data->cellar_color.g = ft_atoi(ceiling[1]);
			data->cellar_color.b = ft_atoi(ceiling[2]);
		}
		str = get_next_line(fd);
	}
	printf("NORTH: |%s|\n", data->north_texture);
	printf("SOUTH: |%s|\n", data->south_texture);
	printf("WEST: |%s|\n", data->west_texture);
	printf("EAST: |%s|\n\n", data->east_texture);

	printf("FLOOR R : |%i|\n", data->floor_color.r);
	printf("FLOOR G : |%i|\n", data->floor_color.g);
	printf("FLOOR B : |%i|\n\n", data->floor_color.b);

	printf("CELLAR R : |%i|\n", data->cellar_color.r);
	printf("CELLAR G : |%i|\n", data->cellar_color.g);
	printf("CELLAR B : |%i|\n", data->cellar_color.b);
}
