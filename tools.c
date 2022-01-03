#include "fillit.h"

int find_best(t_tetr_array *tetriminos, int size)
{
	t_matrix *new;
	t_point start;
	int result = 0;

	start.row = 0;
	start.column = 0;
	new = create_matrix(size);
	if (!new)
		return (-1);
	result = put_tetrimino(tetriminos, new, size, 0);
	free_matrix(new);
	return (result);
}

int put_tetrimino(t_tetr_array *tetriminos, t_matrix *matrix, int size, int index)
{
	int result;
	int if_solution;
	t_point next;

	if (index == tetriminos->size)
		end_game(tetriminos, matrix);
	next.column = 0;
	next.row = 0;
	while (next.column != -1) 
	{
		result = place_tetro(next, matrix, tetriminos->array[index]);
		if (result == 1)
		{
			if_solution = put_tetrimino(tetriminos, matrix, size, index + 1);
			if (if_solution == 1)
			{
				return (1);
			}
			remove_tetro(next, matrix, tetriminos->array[index]);
		}
		next = get_next_coordinate(*matrix, next.row, next.column);
	}
	return (0);
}

t_point	get_next_coordinate(t_matrix matrix, int lastrow, int lastcolumn)
{
	int i = lastrow + lastcolumn;
	int row = lastrow + 1;
	int column = lastcolumn - 1;
	t_point point;

	point.row = -1;
	point.column = -1;
	while (i < matrix.size * 2 - 1)
	{
		while (column >= 0)
		{
			if (row < matrix.size && column < matrix.size && matrix.grid[row][column] == '.')
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

int	place_tetro(t_point start, t_matrix *matrix, t_tetr tetro)
{
	int i;
	int j;
	t_point tetropoint;
	t_point possible;

	tetropoint = find_tetropoint(tetro);
	if (check_tetro(start, matrix, tetro))
	{
		i = tetropoint.column;
		j = tetropoint.row;
		while (j < 4)
		{
			while (i < 4)
			{
				if (tetro.grid[j][i] == '#')
				{
					possible.row = start.row + j - tetropoint.row;
					possible.column = start.column + i - tetropoint.column;
					matrix->grid[possible.row][possible.column] = tetro.symbol;
				}
				i++;
			}
			i = 0;
			j++;
		}
		return (1);
	}
	return (0);
}

int	check_tetro(t_point start, t_matrix *matrix, t_tetr tetro)
{
	int i;
	int j;
	t_point tetropoint;
	t_point possible;

	tetropoint = find_tetropoint(tetro);
	i = tetropoint.column;
	j = tetropoint.row;
	while (j < 4)
	{
		while (i < 4)
		{
			if (tetro.grid[j][i] == '#')
			{
				possible.row = start.row + j - tetropoint.row;
				possible.column = start.column + i - tetropoint.column;
				if (possible.row < 0 || possible.row >= matrix->size || possible.column < 0 || possible.column >= matrix->size || matrix->grid[possible.row][possible.column] != '.')
					return (0);
			}
			i++;
		}
		i = 0;
		j++;
	}
	return (1);
}

t_point find_tetropoint(t_tetr tetro)
{
	int i;
	int j;
	t_point tetropoint;

	tetropoint.row = 0;
	tetropoint.column = 0;
	j = 0;
	while (j < 4)
	{
		i = 0;
		while (i < 4)
		{
			if (tetro.grid[j][i] == '#')
			{
				tetropoint.row = j;
				tetropoint.column = i;
				return (tetropoint);
			}
			i++;
		}
		j++;
	}
	return (tetropoint);
}

int	remove_tetro(t_point start, t_matrix *matrix, t_tetr tetro)
{
	int i;
	int j;
	t_point tetropoint;
	t_point possible;

	tetropoint = find_tetropoint(tetro);
	i = tetropoint.column;
	j = tetropoint.row;
	while (j < 4)
	{
		while (i < 4)
		{
			if (tetro.grid[j][i] == '#')
			{
				possible.row = start.row + j - tetropoint.row;
				possible.column = start.column + i - tetropoint.column;
				matrix->grid[possible.row][possible.column] = '.';
			}
			i++;
		}
		i = 0;
		j++;
	}
	return (1);
}