/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 11:20:15 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/01/06 12:15:29 by nsamoilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

t_point	get_next_coordinate(t_matrix m, int row, int column)
{
	int		i;
	t_point	point;

	i = row + column;
	point.row = -1;
	point.column = -1;
	while (i < m.size * 2 - 1)
	{
		while (column >= 0)
		{
			if (row < m.size && column < m.size && m.grid[row][column] == '.')
			{
				point.row = row;
				point.column = column;
				return (point);
			}
			row++;
			column--;
		}
		i++;
		column = i;
		row = 0;
	}
	return (point);
}

int	put_tetrimino(t_tetr_array *tetros, t_matrix *matrix, int size, int index)
{
	int		result;
	int		if_solution;
	t_point	next;
	t_point	tetropoint;

	if (index == tetros->size)
		end_game(tetros, matrix);
	next.column = 0;
	next.row = 0;
	tetropoint = find_tetropoint(tetros->array[index]);
	while (next.column != -1)
	{
		result = place_tetro(next, matrix, tetros->array[index], tetropoint);
		if (result == 1)
		{
			if_solution = put_tetrimino(tetros, matrix, size, index + 1);
			if (if_solution == 1)
			{
				return (1);
			}
			remove_tetro(next, matrix, tetros->array[index]);
		}
		next = get_next_coordinate(*matrix, next.row + 1, next.column - 1);
	}
	return (0);
}

t_matrix	*create_matrix(int size)
{
	t_matrix	*matrix;
	int			i;
	int			j;

	i = 0;
	j = 0;
	matrix = (t_matrix *)malloc(sizeof(t_matrix));
	matrix->size = size;
	matrix->grid = (char **)malloc(sizeof(char *) * size);
	while (i < size)
	{
		j = 0;
		matrix->grid[i] = (char *)malloc(sizeof(char) * size);
		while (j < size)
		{
			matrix->grid[i][j] = '.';
			j++;
		}
		i++;
	}
	return (matrix);
}

int	find_best(t_tetr_array *tetriminos, int size)
{
	t_matrix	*new;
	int			result ;

	result = 0;
	new = create_matrix(size);
	if (!new)
		return (-1);
	result = put_tetrimino(tetriminos, new, size, 0);
	free_matrix(new);
	return (result);
}
