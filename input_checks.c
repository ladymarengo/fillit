/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 13:32:55 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/01/07 17:31:57 by nsamoilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int	ft_lines_and_char(char *s, int i, int count, int lines)
{
	while (s[i] != '\0')
	{
		if (s[i] != '#' && s[i] != '.' && s[i] != '\n')
			return (-1);
		if (s[i] == '#')
			count++;
		if (s[i] == '\n')
		{
			if (s[i - 1] != '\n')
				lines++;
			if (s[i + 1] == '\n' || s[i + 1] == '\0')
			{
				if (count != 4 || lines != 4)
					return (-1);
				count = 0;
				lines = 0;
			}
		}
		i++;
	}
	i++;
	if (i % 21 != 0)
		return (-1);
	return (1);
}

int	ft_check_tetros(char *s, int i, int connection, int k)
{
	int	j;

	j = 21;
	while (s[i] != '\0')
	{
		if (s[i] == '#')
		{
			if (s[i - 1] == '#' && i - 1 >= k)
				connection++;
			if (s[i - 5] == '#' && i - 5 >= k)
				connection++;
		}
		if ((s[i] == '\n' && s[i + 1] == '\n')
			|| (s[i] == '\n' && s[i + 1] == '\0'))
		{
			if (connection != 3 && connection != 4)
				return (-1);
			j = j + 21;
			k = k + 21;
			connection = 0;
		}
		i++;
	}
	return (1);
}

void	check_input(char *buffer)
{
	if (ft_lines_and_char(buffer, 0, 0, 0) != 1
		|| ft_check_tetros(buffer, 0, 0, 0) != 1)
	{
		ft_putendl("error");
		free(buffer);
		exit(-1);
	}
}
