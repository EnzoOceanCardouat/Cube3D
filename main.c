/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcrenn <mcrenn@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 10:43:52 by mcrenn            #+#    #+#             */
/*   Updated: 2026/10/27 11:10:14 by mcrenn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/parsing.h"

/* Main which is the start of the Cube3D project! */

int main(int ac, char **av)
{
	int	fd;

	if (ac != 2)
		return (1);
	if (ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4) != 0)
	{
		//Error
		return (1);
	}
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		//Error
		return (1);
	}
	parsing(fd);
	return (0);
}
