/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 11:21:50 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/01/06 11:36:37 by nsamoilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	error_exit(int argc)
{
	if (argc != 2)
	{
		ft_putendl("usage: the number of parameters should be one");
		exit(-1);
	}
}

int	main(int argc, char **argv)
{
	int				chars;
	int				file;
	char			*buffer;
	int				size;
	t_tetr_array	tetrimino;

	error_exit(argc);
	buffer = (char *)malloc(sizeof(char) * 1000);
	file = open(argv[1], O_RDONLY);
	chars = read(file, buffer, 1000);
	if (chars > 900 || chars < 1)
	{
		free(buffer);
		return (-1);
	}
	buffer[chars] = '\0';
	close(file);
	tetrimino = parse_input(buffer);
	size = 3;
	while (find_best(&tetrimino, size) == 0)
		size++;
	return (0);
}
